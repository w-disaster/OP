#define ALLOCAVETTORE(VET)\
    VET=(int*)malloc(10*sizeof(int));\
    if(VET!=NULL){\
        for(i=0; i<10; i++){\
            VET[i]=i-1000;\
        }\
    }  
