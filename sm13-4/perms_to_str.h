const char *perms_to_str(char *buf, size_t size, int perms);
/*
    char buf[16];
    perms_to_str(buf, 3, 0640);           // в buf будет строка "rw"
    perms_to_str(buf, sizeof(buf), 0640); // в buf будет строка "rw-r-----"
*/
