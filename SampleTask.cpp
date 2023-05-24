#include <Arduino.h>
#include <WiFi.h>
#include "SampleTask.h"
#include "RemoteBoxControl.h"
#include "SampleMp3Data.h"

const char *ssid = "*****";
const char *passward = "*****";

SampleTask::SampleTask(char *name, uint32_t cycle, uint16_t stack, uint32_t priority, CpuCore core) :
  AbstractTask(name, cycle, stack, priority, core) {
}

namespace {
  void DispHelp() {
    Serial.println("==== Usage ====");
    Serial.println("1 : RemoteBoxControl::Unlock()");
    Serial.println("2 : RemoteBoxControl::Lock()");
    Serial.println("3 : RemoteBoxControl::IsBoxClose()");
    Serial.println("4 : RemoteBoxControl::IsEmergencyState()");
    Serial.println("5 : RemoteBoxControl::GetFoundDeviceInfo()");
    Serial.println("6 : RemoteBoxControl::CtrlDeviceDetectLed(true)");
    Serial.println("7 : RemoteBoxControl::CtrlDeviceDetectLed(false)");
    Serial.println("8 : RemoteBoxControl::SetMp3Data()");
    Serial.println("9 : RemoteBoxControl::StartSound()");
    Serial.println("a : RemoteBoxControl::StopSound()");
  }
}

void SampleTask::Setup() {
  // 本実装はテスト用のサンプルですので、削除頂いて構いません。
  // AWS接続処理開発のご担当者様にて、実装をお願いいたします。
  Serial.println("SampleTask Start");
  DispHelp();

  // WiFi接続処理のサンプルです
  WiFi.disconnect();
  WiFi.softAPdisconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passward);

  // 接続処理
  const int kWiFiConnectLimit = 1;
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("...Connecting to WiFi");
    delay(3000);
    if (++i > kWiFiConnectLimit) {
      // 接続できなかった場合のエラー処理を実装願います
      break;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected");
  } else {
    Serial.println("Connect Failed");
  }
}

void SampleTask::Loop() {
  // 本実装はテスト用のサンプルですので、削除頂いて構いません。
  // AWS接続処理開発のご担当者様にて、実装をお願いいたします。
  auto c = Serial.read();
  if (c == '1') {
    // AWSからの開放許可指令を模擬する
    RemoteBoxControl::Unlock();
  } else if (c == '2') {
    // AWSからの開放禁止指令を模擬する
    auto ret = RemoteBoxControl::Lock();
    if (ret != RemoteBoxControl::BoxControlReselt::kSuccess) {
      Serial.println("Lock Failed because the box is opened");
    }
  } else if (c == '3') {
    // 箱開閉状態を返す
    auto ret = RemoteBoxControl::IsBoxClose();
    if (ret == true) {
      Serial.println("Box Close");
    } else {
      Serial.println("Box Open");
    }
  } else if (c == '4') {
    // エマージェンシモードかどうかを返す
    auto ret = RemoteBoxControl::IsEmergencyState();
    if (ret == true) {
      Serial.println("Emergency mode");
    } else {
      Serial.println("No emergency");
    }
  } else if (c == '5') {
    // タグ情報を返す
    uint32_t count = 0;
    RemoteBoxControl::TagInfo tag_info;
    RemoteBoxControl::GetFoundDeviceInfo(&count, &tag_info);
    if (count == 0) {
      Serial.println("tag not found");
    } else {
      Serial.println("tag found");
      for (int i = 0; i < count; i++) {
        char buf[256] = {0};
        snprintf(buf, sizeof(buf), "%02x %02x %02x %02x %02x %02x %02x %02x",
          tag_info[i][0], tag_info[i][1], tag_info[i][2], tag_info[i][3],
          tag_info[i][4], tag_info[i][5], tag_info[i][6], tag_info[i][7]);
        Serial.println(buf);
      }
    }
  } else if (c =='6') {
    // デバイス検出LEDを点灯させる
    Serial.println("Device Detect LED ON");
    RemoteBoxControl::CtrlDeviceDetectLed(true);
  } else if (c == '7') {
    // デバイス検出LEDを消灯させる
    Serial.println("Device Detect LED OFF");
    RemoteBoxControl::CtrlDeviceDetectLed(false);
  } else if (c == '8') {
    // mp3音源をセットする
    // ここではテストとして、予めROMに配置した配列を読み込ませておりますが
    // AWS連携後は、AWSから受信したmp3データをバイナリ列として第二引数に渡してください
    // ファイル名は任意ですが、必ずスラッシュから開始してください
    RemoteBoxControl::SetMp3Data("/sample.mp3", kSampleMp3Data, sizeof(kSampleMp3Data));
  } else if (c == '9') {
    // ファイル名を指定してmp3音源を再生する
    // 停止するまで繰り返します
    RemoteBoxControl::StartSound("/sample.mp3");
  } else if (c == 'a') {
    // mp3再生を停止させる
    RemoteBoxControl::StopSound();
  }
}

