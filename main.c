// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// 已移除 #include "functions.h"

// Function declarations
void show_today_schedule();
void show_next_schedule();
void add_schedule();
void edit_schedule();

#define MAX_LINE 256

int main() {
    int choice;
    char input[16];
    while (1) {
        printf("\n=== 智慧行程提醒器 ===\n");
        printf("1. 查詢今天行程\n");
        printf("2. 查詢下一筆行程\n");
        printf("3. 新增行程\n");
        printf("4. 修改或刪除行程\n");
        printf("5. 離開\n");
        printf("請選擇：");
        if (!fgets(input, sizeof(input), stdin)) {
            printf("輸入錯誤，請重試。\n");
            continue;
        }
        if (sscanf(input, "%d", &choice) != 1) {
            printf("請輸入有效選項。\n");
            continue;
        }

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
}

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
