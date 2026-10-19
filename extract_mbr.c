#include <stdint.h>
#include <stdio.h>
#include<stdlib.h>

int main(void)
{
    FILE *fp = fopen("MBR1.dd", "rb");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    unsigned char buffer[16];
    size_t n;
    size_t offset = 0;
    int total_bytes=64;
    int r=4;
    int c=16;

    int cnt=1; //byte count
    int s_cnt=446; //starting count for partition tables
    int e_cnt=511; //ending count for partition tables excluding last 2 bytes for siggy



    //declare a 2d array which will store our last 64 bytes containing partition data

    unsigned char** p_table=malloc(r*sizeof(unsigned char*));
    for(int i=0;i<r;i++)
    {
        p_table[i]=malloc(c*sizeof(unsigned char));
    }

    //fill the array originally with 0s to prevent garbage values

    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++)
        {
            p_table[i][j]='0';
        }
    }
    int i=0;
   
        while (((n = fread(buffer, 1, sizeof(buffer), fp)) > 0)) {
           
          printf("%08zx: ", offset);   
         for (size_t k = 0; k < n; k++){
            printf("%02x ", buffer[k]);

            size_t byte_pos = offset + k;
             if (byte_pos >= 446 && byte_pos < 510) {
                size_t idx   = byte_pos - 446;   // 0 to 63 rep
                size_t row   = idx / 16;          // 0 to 3 rep
                size_t col   = idx % 16;          // 0 to 15 rep
                p_table[row][col] = buffer[k];


         }
        
        }

           printf("\n");
            offset += n;
      
         
    }
    
    if (ferror(fp))
        perror("fread");

    fclose(fp);

    printf("\n\n");
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            printf("%02x  ",p_table[i][j]);
        }
        printf("\n");
    }
    return 0;
}