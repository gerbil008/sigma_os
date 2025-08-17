#ifndef STRINGOPS_H
#define STRINGOPS_H

int len(const char* msg){
    int length = 0;
    for(int i = 0; msg[i] != '\0'; i++){
        length++;
    }
    return length;
}

char* merge_char(const char* msg1, const char* msg2, char* buffer){
    for(int i = 0; msg1[i] != '\0'; i++){
        buffer[i] = msg1[i];
    }
    int x = 0;
    for(int i = len(msg1); msg2[x] != '\0'; i++){
        buffer[i] = msg2[x];
        x++;
    }
    buffer[len(msg1)+len(msg2)] = '\0';
    return buffer;
}

char* int_to_cstring(int value, char* buffer) {

    int i = 0;

    // Spezialfall: 0
    if (value == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return buffer;
    }

    // Temporärer Puffer für Ziffern (umgekehrte Reihenfolge)
    char temp[16];
    while (value > 0) {
        temp[i++] = '0' + (value % 10);
        value /= 10;
    }

    // Ziffern in richtiger Reihenfolge ins Ziel kopieren
    int j = 0;
    while (i > 0) {
        buffer[j++] = temp[--i];
    }

    // Nullterminator
    buffer[j] = '\0';
    return buffer;
}

#endif