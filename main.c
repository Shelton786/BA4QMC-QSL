#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char time_utc[21]; 
	// UTC时间，加1为了存储可能的换行符
    char call_sign[21];
    // 呼号，加1为了存储可能的换行符
    char mode[21];
    // 通联模式，加1为了存储可能的换行符
    char frequency[11]; 
	// 频率，加1为了存储可能的换行符
    char qth[2][11];
    // 地址，加1为了存储可能的换行符
    char rst_report[2][6]; 
	// RST报告，加1为了存储可能的换行符
} ContactLog;

void log_contact(ContactLog *log, FILE *file);
void display_contact(ContactLog log);
void search_contact_by_call_sign(const char *call_sign, FILE *file);
void main_menu(FILE *file);

int main() {
    FILE *file = fopen("log_file.txt", "a+"); // 打开文件用于追加和读取
    if (!file) {
        perror("无法打开文件");
        return 1;
    }

    main_menu(file);

    fclose(file); // 关闭文件
    return 0;
}

void log_contact(ContactLog *log, FILE *file) {
    // 清空输入缓冲区，防止读取到错误的数据
    while (getchar() != '\n') continue;

    printf("请输入通联信息：\n");
    printf("时间(UTC): ");
    fgets(log->time_utc, sizeof(log->time_utc), stdin);
    log->time_utc[strcspn(log->time_utc, "\n")] = 0; // 移除换行符

    // 其他字段的输入可以类似地进行
    printf("对方呼号: ");
    fgets(log->call_sign, sizeof(log->call_sign), stdin);
    log->call_sign[strcspn(log->call_sign, "\n")] = 0;

    printf("通联方式: ");
    fgets(log->mode, sizeof(log->mode), stdin);
    log->mode[strcspn(log->mode, "\n")] = 0;

    printf("频率(MHz): ");
    fgets(log->frequency, sizeof(log->frequency), stdin);
    log->frequency[strcspn(log->frequency, "\n")] = 0;

    printf("QTH(收): ");
    fgets(log->qth[0], sizeof(log->qth[0]), stdin);
    log->qth[0][strcspn(log->qth[0], "\n")] = 0;

    printf("QTH(发): ");
    fgets(log->qth[1], sizeof(log->qth[1]), stdin);
    log->qth[1][strcspn(log->qth[1], "\n")] = 0;
    
    printf("RST报告(收): ");
    fgets(log->rst_report[0], sizeof(log->rst_report[0]), stdin);
    log->rst_report[0][strcspn(log->rst_report[0], "\n")] = 0;

    printf("RST报告(发): ");
    fgets(log->rst_report[1], sizeof(log->rst_report[1]), stdin);
    log->rst_report[1][strcspn(log->rst_report[1], "\n")] = 0;

    // 将输入的数据写入文件
    fprintf(file, "【通联记录开始】\n");
    fprintf(file, "时间(UTC): %s\n", log->time_utc);
    fprintf(file, "对方呼号: %s\n", log->call_sign);
    fprintf(file, "通联方式: %s\n", log->mode);
    fprintf(file, "频率(MHz): %s\n", log->frequency);
    fprintf(file, "QTH(收): %s\n", log->qth[0]);
    fprintf(file, "QTH(发): %s\n", log->qth[1]);
    fprintf(file, "RST报告(收): %s\n", log->rst_report[0]);
    fprintf(file, "RST报告(发): %s\n", log->rst_report[1]);
    fprintf(file, "【通联记录结束】\n\n");
    fprintf(file, "\n"); // 添加一个空行作为记录之间的分隔

    printf("\n通联信息已记录。\n");
}

void display_contact(ContactLog log) {
    printf("通联信息：\n");
    printf("时间(UTC): %s\n", log.time_utc);
    printf("对方呼号: %s\n", log.call_sign);
    printf("通联方式: %s\n", log.mode);
    printf("频率(MHz): %s\n", log.frequency);
    printf("QTH(收): %s\n", log.qth[0]);
    printf("QTH(发): %s\n", log.qth[1]);
    printf("RST报告(收): %s\n", log.rst_report[0]);
    printf("RST报告(发): %s\n", log.rst_report[1]);
}

void display_all_contacts(FILE *file) {
    char buffer[256];
    const char *start_delim = "【通联记录开始】";
    const char *end_delim = "【通联记录结束】";
    ContactLog log;

    rewind(file); // 重置文件指针到文件开头

    printf("所有通联信息如下：\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strstr(buffer, start_delim) != NULL) {
            // 读取并显示一条记录
            if (fgets(log.time_utc, sizeof(log.time_utc), file) &&
                fgets(log.call_sign, sizeof(log.call_sign), file) &&
                fgets(log.mode, sizeof(log.mode), file) &&
                fgets(log.frequency, sizeof(log.frequency), file) &&
                fgets(log.qth[0], sizeof(log.qth[0]), file) &&
                fgets(log.qth[1], sizeof(log.qth[1]), file) &&
                fgets(log.rst_report[0], sizeof(log.rst_report[0]), file) &&
                fgets(log.rst_report[1], sizeof(log.rst_report[1]), file)) {
                // 去除每行末尾的换行符
                log.time_utc[strcspn(log.time_utc, "\n")] = 0;
                log.call_sign[strcspn(log.call_sign, "\n")] = 0;
                log.mode[strcspn(log.mode, "\n")] = 0;
                log.frequency[strcspn(log.frequency, "\n")] = 0;
                log.qth[0][strcspn(log.qth[0], "\n")] = 0;
                log.qth[1][strcspn(log.qth[1], "\n")] = 0;
                log.rst_report[0][strcspn(log.rst_report[0], "\n")] = 0;
                log.rst_report[1][strcspn(log.rst_report[1], "\n")] = 0;

                display_contact(log);
            }
            // 跳过结束标记
            fgets(buffer, sizeof(buffer), file);
        }
    }
}

void search_contact_by_call_sign(const char *call_sign, FILE *file) {
    ContactLog log;
    char buffer[256]; // 用于临时存储文件中读取的行
    int found = 0;
    const char *start_delim = "【通联记录开始】";
    const char *end_delim = "【通联记录结束】";

    rewind(file); // 重置文件指针到文件开头

    // 循环直到文件末尾
    while (fgets(buffer, sizeof(buffer), file)) {
        // 检查是否到达了记录的开始
        if (strstr(buffer, start_delim) != NULL) {
            if (fgets(log.time_utc, sizeof(log.time_utc), file) &&
                fgets(log.call_sign, sizeof(log.call_sign), file) &&
                fgets(log.mode, sizeof(log.mode), file) &&
                fgets(log.frequency, sizeof(log.frequency), file) &&
                fgets(log.qth[0], sizeof(log.qth[0]), file) &&
                fgets(log.qth[1], sizeof(log.qth[1]), file) &&
                fgets(log.rst_report[0], sizeof(log.rst_report[0]), file) &&
                fgets(log.rst_report[1], sizeof(log.rst_report[1]), file)) {
                // 去除每行末尾的换行符
                log.time_utc[strcspn(log.time_utc, "\n")] = 0;
                log.call_sign[strcspn(log.call_sign, "\n")] = 0;
                log.mode[strcspn(log.mode, "\n")] = 0;
                log.frequency[strcspn(log.frequency, "\n")] = 0;
                log.qth[0][strcspn(log.qth[0], "\n")] = 0;
                log.qth[1][strcspn(log.qth[1], "\n")] = 0;
                log.rst_report[0][strcspn(log.rst_report[0], "\n")] = 0;
                log.rst_report[1][strcspn(log.rst_report[1], "\n")] = 0;

                // 检查是否匹配呼号
                if (strcmp(log.call_sign, call_sign) == 0) {
                    found = 1;
                    display_contact(log);
                    // 由于已经找到，可以跳出循环
                    break;
                }
            }
            // 跳过当前记录的结束标记
            if (!fgets(buffer, sizeof(buffer), file) || strstr(buffer, end_delim) == NULL) {
                // 如果读取失败或不匹配结束标记，可能是文件格式错误
                fprintf(stderr, "文件格式错误，搜索终止。\n");
                break;
            }
        }
    }

    if (!found) {
        printf("没有找到匹配的呼号：%s。\n", call_sign);
    }
}

void main_menu(FILE *file) {
    int choice;
    char call_sign[21];
    ContactLog log;

    do {
        printf("\n=========================\n");
		printf("业余无线电通联日志程序\n");
        printf("1. 记录通联信息\n");
        printf("2. 显示所有通联信息\n");
        printf("3. 根据呼号查询通联记录\n");
        printf("4. 退出系统\n");
        printf("\n=========================\n");
        printf("请选择操作: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                log_contact(&log, file);
                break;
            case 2:
            	display_all_contacts(file);
                break;
            case 3:
                // 清空输入缓冲区，防止读取到错误的数据
                while (getchar() != '\n') continue;
                
                printf("请输入要查询的呼号: ");
                fgets(call_sign, sizeof(call_sign), stdin); 
				// 使用 fgets 读取一行
                call_sign[strcspn(call_sign, "\n")] = 0; 
				// 移除换行符并添加字符串结束符
                
                search_contact_by_call_sign(call_sign, file);
                break;
            case 4:
                printf("退出程序。\n");
                break;
            default:
                printf("无效选择，请重新输入。\n");
        }
    } while (choice != 4);
    // 只有选择4时退出循环
}
