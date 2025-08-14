#include "cbuffer.h"
using namespace std;
int main() {
    // Khai báo biến circular buffer và bộ nhớ chứa dữ liệu
    cbuffer_t cb;
    uint8_t cb_buff[100]; // Dung lượng = 100, dung lượng thực = 99

    // Khởi tạo buffer
    cb_init(&cb, cb_buff, sizeof(cb_buff));

    // Xóa dữ liệu (reset con trỏ đọc/ghi)
    cb_clear(&cb);

    // Dữ liệu cần ghi
    char a[] = {0, 1, 2, 3, 4};

    // Ghi 5 byte vào buffer
    uint32_t written = cb_write(&cb, a, 5);
    printf("Da ghi %u byte\n", written);

    // Bộ đệm để đọc dữ liệu ra
    char b[5];

    // Đọc 5 byte từ buffer
    uint32_t read_bytes = cb_read(&cb, b, 5);
    printf("Da doc %u byte: ", read_bytes);
    for (uint32_t i = 0; i < read_bytes; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");

    // Kiểm tra trạng thái
    printf("Data count: %u\n", cb_data_count(&cb));
    printf("Space count: %u\n", cb_space_count(&cb));
    printf("Overflow: %u\n", cb.overflow);

    return 0;
}