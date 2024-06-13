#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char time_utc[21]; 
	// UTCʱ�䣬��1Ϊ�˴洢���ܵĻ��з�
    char call_sign[21];
    // ���ţ���1Ϊ�˴洢���ܵĻ��з�
    char mode[21];
    // ͨ��ģʽ����1Ϊ�˴洢���ܵĻ��з�
    char frequency[11]; 
	// Ƶ�ʣ���1Ϊ�˴洢���ܵĻ��з�
    char qth[2][11];
    // ��ַ����1Ϊ�˴洢���ܵĻ��з�
    char rst_report[2][6]; 
	// RST���棬��1Ϊ�˴洢���ܵĻ��з�
} ContactLog;

void log_contact(ContactLog *log, FILE *file);
void display_contact(ContactLog log);
void search_contact_by_call_sign(const char *call_sign, FILE *file);
void main_menu(FILE *file);

int main() {
    FILE *file = fopen("log_file.txt", "a+"); // ���ļ�����׷�ӺͶ�ȡ
    if (!file) {
        perror("�޷����ļ�");
        return 1;
    }

    main_menu(file);

    fclose(file); // �ر��ļ�
    return 0;
}

void log_contact(ContactLog *log, FILE *file) {
    // ������뻺��������ֹ��ȡ�����������
    while (getchar() != '\n') continue;

    printf("������ͨ����Ϣ��\n");
    printf("ʱ��(UTC): ");
    fgets(log->time_utc, sizeof(log->time_utc), stdin);
    log->time_utc[strcspn(log->time_utc, "\n")] = 0; // �Ƴ����з�

    // �����ֶε�����������Ƶؽ���
    printf("�Է�����: ");
    fgets(log->call_sign, sizeof(log->call_sign), stdin);
    log->call_sign[strcspn(log->call_sign, "\n")] = 0;

    printf("ͨ����ʽ: ");
    fgets(log->mode, sizeof(log->mode), stdin);
    log->mode[strcspn(log->mode, "\n")] = 0;

    printf("Ƶ��(MHz): ");
    fgets(log->frequency, sizeof(log->frequency), stdin);
    log->frequency[strcspn(log->frequency, "\n")] = 0;

    printf("QTH(��): ");
    fgets(log->qth[0], sizeof(log->qth[0]), stdin);
    log->qth[0][strcspn(log->qth[0], "\n")] = 0;

    printf("QTH(��): ");
    fgets(log->qth[1], sizeof(log->qth[1]), stdin);
    log->qth[1][strcspn(log->qth[1], "\n")] = 0;
    
    printf("RST����(��): ");
    fgets(log->rst_report[0], sizeof(log->rst_report[0]), stdin);
    log->rst_report[0][strcspn(log->rst_report[0], "\n")] = 0;

    printf("RST����(��): ");
    fgets(log->rst_report[1], sizeof(log->rst_report[1]), stdin);
    log->rst_report[1][strcspn(log->rst_report[1], "\n")] = 0;

    // �����������д���ļ�
    fprintf(file, "��ͨ����¼��ʼ��\n");
    fprintf(file, "ʱ��(UTC): %s\n", log->time_utc);
    fprintf(file, "�Է�����: %s\n", log->call_sign);
    fprintf(file, "ͨ����ʽ: %s\n", log->mode);
    fprintf(file, "Ƶ��(MHz): %s\n", log->frequency);
    fprintf(file, "QTH(��): %s\n", log->qth[0]);
    fprintf(file, "QTH(��): %s\n", log->qth[1]);
    fprintf(file, "RST����(��): %s\n", log->rst_report[0]);
    fprintf(file, "RST����(��): %s\n", log->rst_report[1]);
    fprintf(file, "��ͨ����¼������\n\n");
    fprintf(file, "\n"); // ���һ��������Ϊ��¼֮��ķָ�

    printf("\nͨ����Ϣ�Ѽ�¼��\n");
}

void display_contact(ContactLog log) {
    printf("ͨ����Ϣ��\n");
    printf("ʱ��(UTC): %s\n", log.time_utc);
    printf("�Է�����: %s\n", log.call_sign);
    printf("ͨ����ʽ: %s\n", log.mode);
    printf("Ƶ��(MHz): %s\n", log.frequency);
    printf("QTH(��): %s\n", log.qth[0]);
    printf("QTH(��): %s\n", log.qth[1]);
    printf("RST����(��): %s\n", log.rst_report[0]);
    printf("RST����(��): %s\n", log.rst_report[1]);
}

void display_all_contacts(FILE *file) {
    char buffer[256];
    const char *start_delim = "��ͨ����¼��ʼ��";
    const char *end_delim = "��ͨ����¼������";
    ContactLog log;

    rewind(file); // �����ļ�ָ�뵽�ļ���ͷ

    printf("����ͨ����Ϣ���£�\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strstr(buffer, start_delim) != NULL) {
            // ��ȡ����ʾһ����¼
            if (fgets(log.time_utc, sizeof(log.time_utc), file) &&
                fgets(log.call_sign, sizeof(log.call_sign), file) &&
                fgets(log.mode, sizeof(log.mode), file) &&
                fgets(log.frequency, sizeof(log.frequency), file) &&
                fgets(log.qth[0], sizeof(log.qth[0]), file) &&
                fgets(log.qth[1], sizeof(log.qth[1]), file) &&
                fgets(log.rst_report[0], sizeof(log.rst_report[0]), file) &&
                fgets(log.rst_report[1], sizeof(log.rst_report[1]), file)) {
                // ȥ��ÿ��ĩβ�Ļ��з�
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
            // �����������
            fgets(buffer, sizeof(buffer), file);
        }
    }
}

void search_contact_by_call_sign(const char *call_sign, FILE *file) {
    ContactLog log;
    char buffer[256]; // ������ʱ�洢�ļ��ж�ȡ����
    int found = 0;
    const char *start_delim = "��ͨ����¼��ʼ��";
    const char *end_delim = "��ͨ����¼������";

    rewind(file); // �����ļ�ָ�뵽�ļ���ͷ

    // ѭ��ֱ���ļ�ĩβ
    while (fgets(buffer, sizeof(buffer), file)) {
        // ����Ƿ񵽴��˼�¼�Ŀ�ʼ
        if (strstr(buffer, start_delim) != NULL) {
            if (fgets(log.time_utc, sizeof(log.time_utc), file) &&
                fgets(log.call_sign, sizeof(log.call_sign), file) &&
                fgets(log.mode, sizeof(log.mode), file) &&
                fgets(log.frequency, sizeof(log.frequency), file) &&
                fgets(log.qth[0], sizeof(log.qth[0]), file) &&
                fgets(log.qth[1], sizeof(log.qth[1]), file) &&
                fgets(log.rst_report[0], sizeof(log.rst_report[0]), file) &&
                fgets(log.rst_report[1], sizeof(log.rst_report[1]), file)) {
                // ȥ��ÿ��ĩβ�Ļ��з�
                log.time_utc[strcspn(log.time_utc, "\n")] = 0;
                log.call_sign[strcspn(log.call_sign, "\n")] = 0;
                log.mode[strcspn(log.mode, "\n")] = 0;
                log.frequency[strcspn(log.frequency, "\n")] = 0;
                log.qth[0][strcspn(log.qth[0], "\n")] = 0;
                log.qth[1][strcspn(log.qth[1], "\n")] = 0;
                log.rst_report[0][strcspn(log.rst_report[0], "\n")] = 0;
                log.rst_report[1][strcspn(log.rst_report[1], "\n")] = 0;

                // ����Ƿ�ƥ�����
                if (strcmp(log.call_sign, call_sign) == 0) {
                    found = 1;
                    display_contact(log);
                    // �����Ѿ��ҵ�����������ѭ��
                    break;
                }
            }
            // ������ǰ��¼�Ľ������
            if (!fgets(buffer, sizeof(buffer), file) || strstr(buffer, end_delim) == NULL) {
                // �����ȡʧ�ܻ�ƥ�������ǣ��������ļ���ʽ����
                fprintf(stderr, "�ļ���ʽ����������ֹ��\n");
                break;
            }
        }
    }

    if (!found) {
        printf("û���ҵ�ƥ��ĺ��ţ�%s��\n", call_sign);
    }
}

void main_menu(FILE *file) {
    int choice;
    char call_sign[21];
    ContactLog log;

    do {
        printf("\n=========================\n");
		printf("ҵ�����ߵ�ͨ����־����\n");
        printf("1. ��¼ͨ����Ϣ\n");
        printf("2. ��ʾ����ͨ����Ϣ\n");
        printf("3. ���ݺ��Ų�ѯͨ����¼\n");
        printf("4. �˳�ϵͳ\n");
        printf("\n=========================\n");
        printf("��ѡ�����: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                log_contact(&log, file);
                break;
            case 2:
            	display_all_contacts(file);
                break;
            case 3:
                // ������뻺��������ֹ��ȡ�����������
                while (getchar() != '\n') continue;
                
                printf("������Ҫ��ѯ�ĺ���: ");
                fgets(call_sign, sizeof(call_sign), stdin); 
				// ʹ�� fgets ��ȡһ��
                call_sign[strcspn(call_sign, "\n")] = 0; 
				// �Ƴ����з�������ַ���������
                
                search_contact_by_call_sign(call_sign, file);
                break;
            case 4:
                printf("�˳�����\n");
                break;
            default:
                printf("��Чѡ�����������롣\n");
        }
    } while (choice != 4);
    // ֻ��ѡ��4ʱ�˳�ѭ��
}
