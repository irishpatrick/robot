#ifndef I2C_H
#define I2C_H

typedef struct _I2C
{
    int fp;
    int len;
    unsigned char* buf;
} I2C;

int i2c_connect(I2C*, int);
int i2c_read(I2C*, int);
int i2c_write(I2C*, int);

#endif /* I2C_H */
