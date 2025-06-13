# 📄 智慧行程提醒器

---

## 一、專題摘要

本專題為一個以 C 語言開發的 **CLI（命令列）行程提醒系統**，使用者可新增、查詢、修改與刪除行程，並將行程資料儲存在 `schedule.txt` 檔案中，便於後續查詢與提醒。

本專題開發過程中，大量運用 **生成式 AI 工具（如 ChatGPT、Copilot）**，協助完成程式設計、邏輯規劃、錯誤排除與功能優化，大幅提升開發效率與程式品質，展現出 AI 作為學習與開發助理的強大潛力。

---

## 二、系統設計與流程
- ➕ 新增行程（格式：YYYY/MM/DD HH:MM 活動內容）  
- 📅 查詢今日行程  
- 🔜 查詢下一筆行程（*未來功能*）  
- ✏️ 修改或刪除行程（*進階挑戰*）  
- 🗃 所有行程儲存在 `schedule.txt`

---

## 三、AI 工具協助應用

本專題不直接使用 AI 作為行程解析器，而是將 AI 作為**開發助理工具**，協助以下工作：

| 項目 | 使用 ChatGPT 協助內容 |
|------|------------------------|
| 🧠 專題規劃 | 幫助釐清 CLI 程式的功能模組與流程設計 |
| 🛠 程式撰寫 | 協助撰寫 C 語言邏輯，如時間處理、檔案操作 |
| 🐞 除錯優化 | 協助分析錯誤訊息並提供修正建議 |
| 📐 時間比較 | 指導如何使用 `struct tm` 與 `mktime()` 做時間運算 |
| 🧾 文字格式 | 協助統一行程輸入格式與資料驗證邏輯 |

---

## 四、技術挑戰與解法

| 問題 | 解決方式 |
|------|----------|
| ⏳ 時間比大小困難 | 使用 `struct tm` + `mktime()` 比較時間 |
| 📝 檔案刪除不易 | 改用「讀取 ➜ 修改 ➜ 輸出至暫存檔 ➜ 覆蓋原檔」方式處理 |
| 🧵 字串處理繁瑣 | ChatGPT 提供 `fgets()`、`strtok()` 等範例，簡化實作 |

---

## 五、實作成果與畫面

### ⚙️ 系統功能

- ➕ 新增行程（格式：YYYY/MM/DD HH:MM 活動內容）  
- 📅 查詢今日行程  
- 🔜 查詢下一筆行程（*未來功能*）  
- ✏️ 修改或刪除行程（*進階挑戰*）  
- 🗃 所有行程儲存在 `schedule.txt`
---

## 六、學習心得與收穫

這次專題不僅強化了我在 C 語言的實作能力，更讓我體會到生成式 AI 作為「開發助理」的價值。透過與 AI 對話，我能夠快速釐清邏輯、學習新語法、解決錯誤，大幅提升開發速度與自信心。

未來我將繼續活用 AI 工具於學習與實作中，發展更多實用應用。

---

## 七、原始碼與資源

### 📁 檔案架構


### 📄 原始碼內容

#### ✅ main.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main() {
    int choice;
    while (1) {
        printf("\n=== 智慧行程提醒器 ===\n");
        printf("1. 查詢今天行程\n");
        printf("2. 查詢下一筆行程\n");
        printf("3. 新增行程\n");
        printf("4. 修改或刪除行程\n");
        printf("5. 離開\n");
        printf("請選擇：");
        scanf("%d", &choice);
        getchar(); // 吃掉換行

        switch (choice) {
            case 1:
                show_today_schedule();
                break;
            case 2:
                show_next_schedule();
                break;
            case 3:
                add_schedule();
                break;
            case 4:
                edit_schedule();
                break;
            case 5:
                printf("感謝使用，再見！\n");
                exit(0);
            default:
                printf("請輸入有效選項。\n");
        }
    }
    return 0;
}
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void show_today_schedule();
void show_next_schedule();
void add_schedule();
void edit_schedule();

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

#define MAX_LINE 256

void show_today_schedule() {
    FILE *fp = fopen("schedule.txt", "r");
    if (!fp) {
        printf("無法開啟 schedule.txt\n");
        return;
    }

    char line[MAX_LINE];
    time_t t = time(NULL);
    struct tm *now = localtime(&t);
    char today[11]; // YYYY/MM/DD
    strftime(today, sizeof(today), "%Y/%m/%d", now);

    printf("【今日行程】\n");
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, today, 10) == 0) {
            printf("%s", line);
        }
    }

    fclose(fp);
}

void add_schedule() {
    char new_schedule[MAX_LINE];
    printf("請輸入行程（格式：YYYY/MM/DD HH:MM 活動內容）：\n");
    fgets(new_schedule, MAX_LINE, stdin);

    FILE *fp = fopen("schedule.txt", "a");
    if (!fp) {
        printf("無法寫入 schedule.txt\n");
        return;
    }
    fputs(new_schedule, fp);
    fclose(fp);

    printf("✅ 行程已新增！\n");
}

void show_next_schedule() {
    printf("🔜 此功能可依照時間排序 schedule.txt 內的內容後顯示下一筆，目前尚未實作排序功能。\n");
}

void edit_schedule() {
    printf("✏️ 修改/刪除功能為進階挑戰，可使用臨時檔案方式重寫 schedule.txt。\n");
}
