#include<stdio.h>
#include<string.h>
#define N strlen(gen_poly)
char data[28];
char check_value[28];
char gen_poly[10]; 
int data_length,i,j;

void XOR(){
    for(j = 1;j < N; j++){
        check_value[j] = (( check_value[j] == gen_poly[j])?'0':'1');
    }
}

void crc(){
    for(i=0;i<N;i++){
        check_value[i]=data[i];       
    }

    do{
        if(check_value[0]=='1')
            XOR();
        for(j=0;j<N-1;j++)
            check_value[j]=check_value[j+1];
        check_value[j]=data[i++];
    }while(i<=data_length+N-1);
}

void receiver(){
    printf("\n--------Error Detection--------\n");
    printf("\nEnter the received data: ");
    scanf("%s", data);
    printf("\n Data received: %s", data);
    crc();
    for(i=0;(i<N-1) && (check_value[i]!='1');i++);
        if(i<N-1)
            printf("\n Error detected\n\n");
        else
            printf("\n No error detected\n\n");  
}

void sender(){
    printf("\n--------Data Transmission--------\n");
    printf("\nEnter data to be transmitted: ");
    scanf("%s",data);
    printf("Enter the Generating polynomial: ");
    scanf("%s",gen_poly);
    data_length=strlen(data);
    for(i=data_length;i<data_length+N-1;i++){
        data[i]='0';
    }
    printf("\n Data padded with n-1 zeros : %s",data);
    crc();
    printf("\n CRC or Check value is : %s",check_value);  
    for(i=data_length;i<data_length+N-1;i++){
        data[i]=check_value[i-data_length];
    }
    printf("\n Final data to be sent : %s\n",data);
}

int main()
{
    int func;
    printf("------------CRC----------\n\n");
    printf("1 -> Code Generation\n2 -> Error Detection\n3 ->Both\n\n");
    printf("Enter the operation to be done: ");
    scanf("%d",&func);
    switch(func){
        case 1:
            sender();
            break;

        case 2:
            receiver();
            break;
        
        case 3:
            sender();
            receiver();
            break;
        default:
            printf("Please enter a valid operation!!");
    }
    return 0;
}
