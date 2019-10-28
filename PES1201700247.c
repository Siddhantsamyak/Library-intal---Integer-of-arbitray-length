#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"intal.h"
#define conv_char_int(c) (int)c - (int)'0'

static char* string_reverse(char *str,int n);

char* intal2str(void* intal)
{
    if(intal==NULL)
    {

    char*str=(char*)malloc(sizeof(char)*4);
    char str1[4]="NaN";
    strcpy(str,str1);
        return str;
    }
    else
    {

    intal=(char*)intal;
    long int l=strlen(intal);
    char *str=(char*)malloc(sizeof(char)*l);
    strcpy(str,intal);
    
    intal=(void*)intal;
    return str;
         
    }
}

void* intal_diff(void* intal1, void* intal2)
{
    if(intal1==NULL || intal2==NULL)
     {
             return (void*)NULL;
        }
    char*string1,*string2,*final,temp;
    string1=(char*)intal1;
    string2=(char*)intal2;
    char*str1=(char*)malloc(sizeof(char)*(strlen(string1)));
    char*str2=(char*)malloc(sizeof(char)*(strlen(string2)));
    strcpy(str1,string1);
    strcpy(str2,string2);
    
    int cmp=intal_compare(str1,str2);
    if(cmp==-1)
    {
        char*temp=(char*)malloc(sizeof(char)*strlen(str1));
        char*temp1=(char*)malloc(sizeof(char)*strlen(str2));
        strcpy(temp,str1);
        strcpy(temp1,str2);
        str1=(char*)realloc(str1,strlen(str2));
        str2=(char*)realloc(str2,strlen(str1));
        strcpy(str1,temp1);
        strcpy(str2,temp);
    }
    
    str1=string_reverse(str1,strlen(str1));
    str2=string_reverse(str2,strlen(str2));
    
    long int l1=strlen(str1);
    long int l2=strlen(str2);
    
    long int k=0;
    int carry=0;
    final=(char*)malloc(sizeof(char)*(l1+1));
    for(long int i=0;i<l2;i++)
    {
        
        int sub = ((str1[i]-'0')-(str2[i]-'0')-carry); 
        if (sub < 0) 
            { 
                    sub = sub + 10; 
                    carry = 1; 
            } 
             else
        {
                carry = 0; 
        }
        final[k++]=sub+'0';
    }
    
    for(long int i=l2;i<l1;i++)
    {
        int sub = ((str1[i]-'0') - carry); 
        if (sub < 0) 
             { 
            sub = sub + 10; 
            carry = 1; 
             } 
            else
        {
                    carry = 0; 
        }
        final[k++]=sub+'0';
    
        
    }
    final[k]='\0';
    
    final=string_reverse(final,strlen(final));
    
    final=intal_create(final);
    
    return (void*)final;
}

void* intal_divide(void* intal1, void* intal2)
{
    
    if(intal1==NULL || intal2==NULL)
    {
        
        return (void*)NULL;
    }
    int flag1=intal_compare(intal1,intal_create("0"));
    int flag2=intal_compare(intal2,intal_create("0"));
    if(flag2==0)
    {
        
        return (void*)NULL;
    }
    if(flag1==0)
    {
        return intal_create("0");
    }
    int flag3=intal_compare(intal1,intal2);
    if(flag3==-1)
    {
        return intal_create("0");
    }

    void *s1=intal_create((char*)(intal1));
    void *s2=intal_create((char*)(intal2));
    void *quotient=intal_create("0");
    int cmp=intal_compare(s1,intal_create("0"));
    while(cmp==1)
    {
        s1=intal_diff(s1,s2);
        cmp=intal_compare(s1,s2);
        quotient=intal_increment(quotient);
    }
    return quotient;
}

void* intal_decrement(void* intal)
{
    if(intal==NULL)
    {
        return (void*)NULL;
    }
    char*str1=(char*)intal;
    char*s=(char*)malloc(sizeof(char)*2);
    strcpy(s,str1);
    char *final=(char*)malloc(sizeof(char)*(strlen(str1)));
    if(strlen(s)==1)
    {
        

        int diff=(s[0]-'0')-1;
        if(diff<0)
        {
            s[0]='0';
            
        }
        else
        {
            s[0]=diff+'0';
        }
        return (void*)s;
    }
    else
    {
        char str1[1]="1";
        final=intal_diff(s,str1);
        final=intal_create(final);
        intal_destroy(intal);
        return (void*)final;
    }
}
			
static char* string_reverse(char *str,int n)
{
	char s1;
	for(int i=0;i<n/2;i++)
	{
		s1=str[i];
		str[i]=str[n-i-1];
		str[n-i-1]=s1;
	}
    	str[n]='\0';
	return str;
}	
	
int intal_compare(void* intal1, void* intal2)
{
    if(intal1==NULL || intal2==NULL)
    {
        return -2;
    }
    char*s1=(char*)intal1;
    char*s2=(char*)intal2;
    
    long long int length1=strlen(s1);
    long long int length2=strlen(s2);
    long long int length3=0;
    if(length1>length2)
    {
        return 1;
    }
    else if(length1<length2)
    {
        return -1;
    }
    else if(length1==length2)
    {
        for(long long int i=0;i<length1;i++)
        {
            if(s1[i]-'0' > s2[i]-'0')
            {
                return 1;
            }
            else if(s1[i]-'0' < s2[i]-'0')
            {
                return -1;
            }
            else
            {
                length3=length3+1;
            }
        }
        return 0;
    }
}

void* intal_increment(void* intal)
{
	if(intal==NULL)
	{
		return (void*)NULL;
	}
	char *s1=(char*)intal;
	char *s2=(char*)malloc(sizeof(char)*(strlen(s1)));
	strcpy(s2,s1);
	char *str=(char*)malloc(sizeof(char)*(strlen(s2)+1));
	long long int i=0;
	int incre=0;
	int var;
	long long int j=0;
	s2=string_reverse(s2,strlen(s2));
	
	while(i<strlen(s2))
	{
		
		if(i==0)
		{
			var=s2[i]-'0';
			var=var+1;
			incre=var/10;
			var=var%10;
		}
		else
		{
			var=s2[i]-'0';
			var=var+incre;
			incre=var/10;
			var=var%10;
		}
		
		str[j++]=var+'0';
		
		i=i+1;
		
	}
		
	if(incre!=0)
	{
		str[j++]=incre+'0';
	}
	str[j]='\0';
		
	str=string_reverse(str,strlen(str));
	str=intal_create(str);
	intal=(void*)intal;
	intal_destroy(intal);
	return str;
}

void* intal_add(void* intal1, void* intal2)
{
    if(intal1==NULL || intal2==NULL)
    {
        return (void*)NULL;
    }
    char*string1,*string2,*s3;
    string1=(char*)intal1;
    string2=(char*)intal2;
    char*str1=(char*)malloc(sizeof(char)*(strlen(string1)));
    char*str2=(char*)malloc(sizeof(char)*(strlen(string2)));
    strcpy(str1,string1);
    strcpy(str2,string2);
    long long int length1=strlen(str1);
    long long int length2=strlen(str2);
    long long int diff,carry,sum,j,max,i,min;
    
    carry=0;
    j=0;
    i=0;
    if(length1>length2)
    {
        s3=(char*)malloc(sizeof(char)*(length1+1));
    }
    else if(length1<length2)
    {
        
        s3=(char*)malloc(sizeof(char)*(length2+1));
    }
    else
    {
        s3=(char*)malloc(sizeof(char)*(length1+1));
    }
    str1=string_reverse(str1,strlen(str1));
    str2=string_reverse(str2,strlen(str2));
    if(length1>length2)
    {
        diff=length1-length2;
    }
    else
    {
        diff=length2-length1;
    }
    if(length1<length2)
    {
        max=length2;
        min=length1;
    }
    else
    {
        max=length1;
        min=length2;
    }
    
    
    while(i<min)
    {
        if(i==0)
        {
            sum=str1[i]-'0' + str2[i]-'0';
            carry=sum/10;
            sum=sum%10;
        }
        else
        {
            sum=str1[i]-'0' + str2[i]-'0' +carry;
            carry=sum/10;
            sum=sum%10;
        }
        s3[j++]=sum+'0';
        i=i+1;
        
    }
    
    if(max==length1)
    {
        while(i<length1)
        {
            sum=str1[i]-'0'+carry;
            carry=sum/10;
            sum=sum%10;
            i=i+1;
            s3[j++]=sum+'0';
        }
    }
    else if(max==length2)
    {
        while(i<length2)
        {
            sum=str2[i]-'0'+carry;
            carry=sum/10;
            sum=sum%10;
            i=i+1;
            s3[j++]=sum+'0';
        }
    }
    if(carry!=0)
    {
        s3[j++]=carry+'0';
    }
    s3[j]='\0';
    s3=string_reverse(s3,strlen(s3));
    return (void*)s3;
    
}

void* intal_multiply(void* intal1, void* intal2)
{
    if(intal1==NULL || intal2==NULL)
    {
        return (void*)NULL;
    }
    long int length1=strlen(intal1);
    long int length2=strlen(intal2);
    
    char*s1,*s2;
    if(length1>length2)
    {
        length1=length1+length2;
        length2=length1-length2;
        length1=length1-length2;
        s1=intal2;
        s2=intal1;
    }
    else
    {
        s1=intal1;
        s2=intal2;
    }
    
    long int i,j,totallen,carry,product;
    totallen=length1+length2;
    char*s3=(char*)malloc(sizeof(char)*(totallen+1));
    carry=0;
    for(i=0;i<totallen;i++)
    {
        s3[i]='0';
    }
    s3[totallen]='\0';
    for(i=length2-1;i>=0;i--)
    {
        totallen=(length1+length2-1)-((length2-1)-i);
        for(j=length1-1;j>=0;j--)
        {
            product=(((int)*(s1+j)) - 48) * (((int)*(s2+i))-48);
        
            carry = carry+product+((int)*(s3+totallen)-48);
            *(s3+totallen)=(char)(48+(carry%10));
                totallen--;
            carry=carry/10;
        }
        *(s3+totallen)=(char)(48+((int)*(s3+totallen)-48)+carry);
            carry = 0;  
    }

    
    return intal_create(s3);
}   

void* intal_pow(void* intal1, void* intal2)
{
    if(intal1==NULL || intal2==NULL)
    {
        return (void*)NULL;
    }

    int flag1 = intal_compare(intal1,intal_create("0"));
    int flag2 = intal_compare(intal2,intal_create("0"));
    if(flag1==0 && flag2==0)
    {
        return intal_create("0");
    }
    if(flag2==0)
    {
        return intal_create("1");
    }
    if(flag1==0)
    {
        return intal_create("0");
    }

    void *final3=intal_create((char*)(intal2));
    void *pow=intal_create("1");
    int cmp=intal_compare(final3,intal_create("0"));
    while(cmp==1)
    {
        
        (void*)intal1; (void*)pow;
        pow=intal_multiply(pow,intal1);
        final3=intal_decrement(final3);
        cmp=intal_compare(final3,intal_create("0"));
    }
    
    return pow;
}

void* intal_create(const char* str)
{
	int length = strlen(str);
	if(length==0 || conv_char_int(*(str+0))>9 || conv_char_int(*(str+0))<0)
   	{
      		char * arr = (char*)malloc(sizeof(char));
        	*arr = '0';
        	*(arr+1)='\0';
        	return (void*)arr;
    	}
    	int zero_ctr=0;
    	while(*(str+zero_ctr)!='\0' && conv_char_int(*(str+zero_ctr))==0)
   	{
        	zero_ctr++;
    	}
    	if(length==(zero_ctr) || conv_char_int(*(str+zero_ctr))>9 || conv_char_int(*(str+zero_ctr))<0)
    	{
        	char * arr = (char*)malloc(sizeof(char));
        	*arr = '0';
        	*(arr+1)='\0';
        	return (void*)arr;
    	}
    	char * arr=(char*)malloc((length-zero_ctr+1)*sizeof(char));
   	int i = zero_ctr;
    	int j = 0;
    	while( *(str+i)!='\0' && conv_char_int(*(str+i))>=0 && conv_char_int(*(str+i))<=9 )
    	{
        	*(arr+j)=*(str+i);
        	i++;
        	j++;
    	}
    	*(arr+j)='\0';
    	if(j!=(length-zero_ctr))
    	{
        	arr = realloc(arr,(j+1)*sizeof(char));
    	}
    	return (void*)arr;
}

void intal_destroy(void* intal)
{
	if(intal==NULL)
	{
		return;
	}
	free(intal);
}

