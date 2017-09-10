/*
NFA_TO_DFA
DAA PROJECT DONE BY:
1) Udupi Katte Harshith
   01FB14ECS268
2) Sreevardhan S.
   01FB14ECS249
3) Mayank S.K.
   01FB14ECS194
*/
#include "nfa_to_dfa.h"
void create_nfa_file(char* fname)
{
    FILE* fp = fopen(fname,"r");
    char ch;
    int lcount=0,n=0;
    char str[60];
    if(fp==NULL)
    {
        printf("\nThe File which you specified does not exist!\n");
    }
    while(fgets(str,60,fp)!=NULL)
    {
        if(lcount==0)
        {
            int i=0,l=0,is_l=0;
            while(str[i]!='\0')
            {
                if(str[i]=='\t')
                {
                    ++l;
                }
                else if(str[i]=='~')
                {
                    is_l = 1;
                }
                ++i;
            }
            alphabets = (char*)malloc((l+1)*sizeof(char));
            if(is_l)
            {
                alpha_num = l;
            }
            else
            {
                alpha_num = l+1;
            }
            l = 0;
            i = 0;
            while(str[i]!='\0')
            {
                if(str[i]!='\t' && str[i]!='\n')
                {
                    alphabets[l++] = str[i];
                }
                ++i;
            }
            if(!is_l)
            {
                alphabets[l++] = '~';
            }
        }
        lcount++;
    }
    int k;
    n_array = (Node**)malloc((lcount-3)*sizeof(Node*));
    state_num = lcount-3;
    for(k=0; k<state_num; ++k)
    {
        n_array[k] = (Node*)malloc(sizeof(Node));
        n_array[k]->l = NULL;
        n_array[k]->t = (Node**)malloc((alpha_num+1)*sizeof(Node*));
        n_array[k]->n_no = k;
        n_array[k]->n_lt = 0;
        n_array[k]->is_final = 0;
    }
    fp = fopen(fname,"r");
    lcount = 0;
    int is_f = 0;
    while(fgets(str,60,fp)!=NULL)
    {
        if(lcount!=0 && strcmp(str,"\n")!=0)
        {
            if(!is_f)
            {
                int i=0,j=0,is_c=0;
                while(str[i]!='\0')
                {
                    int a=0,count=0;
                    if(alphabets[j]!='~')
                    {
                        while(str[i]!='\t' && str[i]!='\n' && str[i]!=',')
                        {
                            if(str[i]!='-')
                            {
                                a = a*10 + (str[i]-'0');
                            }
                            else
                            {
                                break;
                            }
                            ++i;
                        }
                        if(str[i]!='-')
                        {
                            if(!is_c)
                            {
                                n_array[lcount-1]->t[j] = n_array[a];
                            }
                            else
                            {
                                count++;
                                if(n_array[lcount-1]->l==NULL)
                                {
                                    n_array[lcount-1]->l = (Node**)malloc(count*sizeof(Node*));
                                }
                                else
                                {
                                    n_array[lcount-1]->n_lt++;
                                    n_array[lcount-1]->l = (Node**)realloc(n_array[lcount-1]->l,count*sizeof(Node*));
                                }
                                state_num++;
                                n_array = (Node**)realloc(n_array,state_num*sizeof(Node*));
                                n_array[state_num-1] = (Node*)malloc(sizeof(Node));
                                n_array[state_num-1]->is_final = 0;
                                n_array[state_num-1]->l = NULL;
                                n_array[state_num-1]->n_no = state_num-1;
                                n_array[state_num-1]->n_lt = 0;
                                n_array[state_num-1]->t = (Node**)malloc((alpha_num+1)*sizeof(Node*));
                                n_array[lcount-1]->l[count-1] = n_array[state_num-1];
                                n_array[lcount-1]->n_lt++;
                                n_array[state_num-1]->t[j] = n_array[a];
                                for(k=0; k<alpha_num+1; ++k)
                                {
                                    if(k!=j)
                                    {
                                        n_array[state_num-1]->t[k] = NULL;
                                    }
                                }
                                is_c = 0;
                            }
                            if(str[i]==',')
                            {
                                is_c = 1;
                            }
                            if(str[i]=='\t')
                            {
                                j++;
                                count=0;
                            }
                            ++i;
                        }
                        else
                        {
                            n_array[lcount-1]->t[j] = NULL;
                            i+=2;
                            ++j;
                            count = 0;
                        }
                    }
                    else
                    {
                        while(str[i]!='\t' && str[i]!='\n' && str[i]!=',')
                        {
                            if(str[i]!='-')
                            {
                                a = a*10 + (str[i]-'0');
                            }
                            else
                            {
                                break;
                            }
                            ++i;
                        }
                        if(str[i]!='-')
                        {
                            if(n_array[lcount-1]->l==NULL && !is_c)
                            {
                                count++;
                                n_array[lcount-1]->l = (Node**)malloc(sizeof(Node*));
                                n_array[lcount-1]->l[0] = n_array[a];
                                n_array[lcount-1]->n_lt = count;
                            }
                            else
                            {
                                count = n_array[lcount-1]->n_lt + 1;
                                n_array[lcount-1]->l = (Node**)realloc(n_array[lcount-1]->l,count*sizeof(Node*));
                                n_array[lcount-1]->l[count-1] = n_array[a];
                                is_c = 0;
                                n_array[lcount-1]->n_lt++;
                            }
                            if(str[i]==',')
                            {
                                is_c = 1;
                            }
                            if(str[i]=='\t')
                            {
                                j++;
                                count=0;
                            }
                            ++i;
                        }
                        else
                        {
                            i+=2;
                            ++j;
                            count = 0;
                        }
                    }
                }
            }
            else
            {
                int i=0;
                while(i<strlen(str))
                {
                    int a=0;
                    while(i<strlen(str) && str[i]!='\t' && str[i]!='\n')
                    {
                        a = a*10 + (str[i]-'0');
                        ++i;
                    }
                    n_array[a]->is_final = 1;
                    ++i;
                }
            }
        }
        else if(lcount!=0)
        {
            is_f = 1;
        }
        lcount++;
    }
    if(n_array!=NULL)
    {
        printf("\nNFA is created from the file successfully!\n");
    }
}
void convert()
{
    int cs = 0,count = 0, cr = 0;
    int* d = NULL;
    int** dstates = NULL;
    int** dtransit = NULL;
    Set* c1 = (Set*)malloc(sizeof(Set));
    c1->head = NULL;
    add(c1,cs);
    count++;
    dstates = (int**)malloc(count*sizeof(int*));
    dtransit = (int**)malloc(sizeof(int*));
    dtransit[0] = (int*)malloc((alpha_num)*(sizeof(int)));
    Set* c2 = (Set*)malloc(sizeof(Set));
    c2->head = NULL;
    LNode* tc = c1->head;
    int len=0;
    while(tc!=NULL)
    {
        cs = tc->data;
        int j;
        ++len;
        for(j=0; j<n_array[cs]->n_lt; ++j)
        {
            add(c1,n_array[cs]->l[j]->n_no);
        }
        if(d==NULL)
        {
            d = (int*)malloc(len*sizeof(int));
            d[len-1] = cs;
        }
        else
        {
            d = (int*)realloc(d,len*sizeof(int));
            d[len-1] = cs;
        }
        tc = tc->next;
    }
    d = (int*)realloc(d,(len+1)*sizeof(int));
    d[len] = -1;
    dstates[0] = d;
    int dalpha[alpha_num];
    while(cr!=count)
    {
        while(1)
        {
            LNode* tc;
            tc = c1->head;
            while(tc!=NULL)
            {
                tc = tc->next;
            }
            int j,nj=0;
            for(j=0; j<alpha_num+1; ++j)
            {
                int len=0;
                d = NULL;
                tc = c1->head;
                while(tc!=NULL)
                {
                    cs = tc->data;
                    if(alphabets[j]!='~' && n_array[cs]->t[j]!=NULL)
                    {
                        add(c2,n_array[cs]->t[j]->n_no);
                    }
                    tc = tc->next;
                }
                tc = c2->head;
                while(tc!=NULL)
                {
                    cs = tc->data;
                    int k;
                    len++;
                    for(k=0; k<n_array[cs]->n_lt; ++k)
                    {
                        add(c2,n_array[cs]->l[k]->n_no);
                    }
                    if(d==NULL)
                    {
                        d = (int*)malloc(len*sizeof(int));
                        d[len-1] = tc->data;
                    }
                    else
                    {
                        d = (int*)realloc(d,len*sizeof(int));
                        d[len-1] = tc->data;
                    }
                    tc = tc->next;
                }
                len++;
                d = (int*)realloc(d,len*sizeof(int));
                d[len-1] = -1;
                int i;
                int k;
                for(k=0; k<count; ++k)
                {
                    int i;
                    for(i=0; i<len; ++i)
                    {
                        if(dstates[k][i]!=d[i])
                        {
                            break;
                        }
                    }
                    if(i==len)
                    {
                        break;
                    }
                }
                if(k==count && alphabets[j]!='~')
                {
                    count++;
                    dstates = (int**)realloc(dstates,count*sizeof(int*));
                    dstates[count-1] = d;
                    dtransit = (int**)realloc(dtransit,count*sizeof(int*));
                    dtransit[count-1] = (int*)malloc((alpha_num+1)*sizeof(int));
                }
                dalpha[nj++] = k;
                c2->head = NULL;
            }
            break;
        }
        dtransit[cr] = (int*)malloc((alpha_num)*sizeof(int));
        int i;
        int j = 0;
        for(i=0; i<alpha_num+1; ++i)
        {
            if(alphabets[i]!='~')
            {
                dtransit[cr][i] = dalpha[j++];
            }
        }
        cr++;
        c1->head = NULL;
        if(cr!=count)
        {
            for(i=0; dstates[cr][i]!=-1; ++i)
            {
                add(c1,dstates[cr][i]);
            }
        }
    }
    int i;
    d_array = (Node**)malloc(count*sizeof(Node));
    for(i=0; i<count; ++i)
    {
        d_array[i] = (Node*)malloc(sizeof(Node));
        d_array[i]->n_no = i;
        d_array[i]->l = NULL;
        d_array[i]->t = (Node**)malloc((alpha_num+1)*sizeof(Node*));
        d_array[i]->n_lt = 0;
        d_array[i]->is_final = 0;
        int j;
        for(j=0; dstates[i][j]!=-1; ++j)
        {
            if(n_array[dstates[i][j]]->is_final)
            {
                break;
            }
        }
        if(dstates[i][j]!=-1)
        {
            d_array[i]->is_final = 1;
        }
    }
    for(i=0; i<count; ++i)
    {
        int j;
        for(j=0; j<alpha_num+1; ++j)
        {
            if(alphabets[j]!='~')
            {
                d_array[i]->t[j] = d_array[dtransit[i][j]];
            }
        }
    }
    state_num = count;
    nfa = 0;
    printf("\nThe given NFA is converted to DFA successfully!\n");
}
int test(char* input)
{
    if(nfa)
    {
        int i,j,cs=0;
        Set* c1 = (Set*)malloc(sizeof(Set));
        c1->head = NULL;
        add(c1,cs);
        Set* c2 = (Set*)malloc(sizeof(Set));
        c2->head = NULL;
        for(i=0; input[i]!='\0'; ++i)
        {
            for(j=0; j<alpha_num; ++j)
            {
                if(input[i]==alphabets[j])
                {
                    break;
                }
            }
            LNode* curr = c1->head;
            while(curr!=NULL)
            {
                cs = curr->data;
                if(n_array[cs]->t[j]!=NULL)
                {
                    add(c2,n_array[cs]->t[j]->n_no);
                }
                int k;
                for(k=0; k<n_array[cs]->n_lt; ++k)
                {
                    add(c1,n_array[cs]->l[k]->n_no);
                }
                curr = curr->next;
            }
            c1->head = c2->head;
            c2->head = NULL;
        }
        LNode* curr = c1->head;
        while(curr!=NULL)
        {
            if(n_array[curr->data]->is_final)
            {
                return 1;
            }
            curr = curr->next;
        }
        return 0;
    }
    else
    {
        int i,j,cs=0;
        for(i=0; input[i]!='\0'; ++i)
        {
            for(j=0; j<alpha_num; ++j)
            {
                if(input[i]==alphabets[j])
                {
                    break;
                }
            }
            if(d_array[cs]->t[j]!=NULL)
            {
                cs = d_array[cs]->t[j]->n_no;
            }
            else
            {
                return 0;
            }
        }
        return d_array[cs]->is_final;
    }
}
void display(int t)
{
    Set* fs = (Set*)malloc(sizeof(Set));
    fs->head = NULL;
    if(t)
    {
        printf("\nTransitions of ");
        if(nfa)
        {
            printf("NFA :");
        }
        else
        {
            printf("DFA :");
        }
        int i,j;
        for(i=0; i<state_num; ++i)
        {
            for(j=0; j<alpha_num+1; ++j)
            {
                if(nfa)
                {
                    if(alphabets[j]=='~')
                    {
                        int k;
                        for(k=0; k<n_array[i]->n_lt; ++k)
                        {
                            printf("\nT(q%d,%c) = q%d",i,alphabets[j],n_array[i]->l[k]->n_no);
                        }
                    }
                    else
                    {
                        if(n_array[i]->t[j]!=NULL)
                        {
                            printf("\nT(q%d,%c) = q%d",i,alphabets[j],n_array[i]->t[j]->n_no);
                        }
                    }
                    if(n_array[i]->is_final)
                    {
                        add(fs,i);
                    }
                }
                else
                {
                    if(d_array[i]->t[j]!=NULL && alphabets[j]!='~')
                    {
                        printf("\nT(q%d,%c) = q%d",i,alphabets[j],d_array[i]->t[j]->n_no);
                    }
                    if(d_array[i]->is_final)
                    {
                        add(fs,i);
                    }
                }
            }
        }
    }
    else
    {
        int i,j;
        printf("S/A");
        for(i=0; i<alpha_num+1; ++i)
        {
            printf("\t%c",alphabets[i]);
        }
        for(i=0; i<state_num; ++i)
        {
            printf("\nq%d",i);
            for(j=0; j<alpha_num+1; ++j)
            {
                if(nfa)
                {
                    if(alphabets[j]=='~')
                    {
                        printf("\t");
                        int k;
                        for(k=0; k<n_array[i]->n_lt; ++k)
                        {
                            printf("%d",n_array[i]->l[k]->n_no);
                            if(k!=(n_array[i]->n_lt)-1)
                            {
                                printf(",");
                            }
                        }
                        if(n_array[i]->n_lt==0)
                        {
                            printf("-");
                        }
                    }
                    else
                    {
                        if(n_array[i]->t[j]!=NULL)
                        {
                            printf("\t%d",n_array[i]->t[j]->n_no);
                        }
                        else
                        {
                            printf("\t-");
                        }
                    }
                    if(n_array[i]->is_final)
                    {
                        add(fs,i);
                    }
                }
                else
                {
                    //printf("%c",alphabets[j]);
                    if(d_array[i]->t[j]!=NULL && alphabets[j]!='~')
                    {
                        printf("\t%d",d_array[i]->t[j]->n_no);
                    }
                    else
                    {
                        printf("\t-");
                    }
                    if(d_array[i]->is_final)
                    {
                        add(fs,i);
                    }
                }
            }
        }
    }
    printf("\nFinal States : ");
    LNode* curr = fs->head;
    while(curr!=NULL)
    {
        printf("%d ",curr->data);
        curr = curr->next;
    }
    printf("\n");
}
int main()
{
    int ch;
    do
    {
        printf("\n---MENU---\n");
        printf("\n1.Create NFA from a file.");
        printf("\n2.Convert the NFA to DFA.");
        printf("\n3.Test the input string.");
        printf("\n4.Display.");
        printf("\n5.Exit.\n");
        do
        {
            printf("\nType a valid option:");
            scanf("%d",&ch);
        }
        while(ch<1 || ch>5);
        if(ch==1)
        {
            char ch = 'y';
            if(n_array!=NULL)
            {
                printf("\nThere is already an NFA. Do you want to replace it?(y/n)");
                do
                {
                    printf("\nType a valid operation: ");
                    scanf("%c",&ch);
                }
                while(ch!='y' && ch!='n');
            }
            if(ch=='y')
            {
                char fname[30];
                printf("\nEnter the file name: ");
                scanf("%s",fname);
                create_nfa_file(fname);
            }
        }
        else if(ch==2)
        {
            if(n_array==NULL && d_array==NULL)
            {
                printf("\nYou do not have an NFA or a DFA!\n");
            }
            else
            {
                if(nfa)
                {
                    convert();
                }
                else
                {
                    printf("\nYou already have a DFA!");
                }
            }
        }
        else if(ch==3)
        {
            if(n_array==NULL && d_array==NULL)
            {
                printf("\nYou do not have an NFA or a DFA!\n");
            }
            else
            {
                char ch;
                do
                {
                    char input[50];
                    printf("\nEnter the input string : ");
                    scanf("%s",input);
                    if(test(input))
                    {
                        printf("\nThe String is accepted!\n");
                    }
                    else
                    {
                        printf("\nThe String is not accepted!\n");
                    }
                    printf("\nDo you want to continue?(y/n)");
                    scanf("%c",&ch);
                    while(ch!='y' && ch!='n')
                    {
                        printf("\nPlease enter a valid option!(y/n)");
                        scanf("%c",&ch);
                    }
                }
                while(ch=='y');
            }
        }
        else if(ch==4)
        {
            if(n_array==NULL && d_array==NULL)
            {
                printf("\nYou do not have an NFA or a DFA!\n");
            }
            else
            {
                char ch;
                printf("\nDo you want to display it in the form of transitions or in the form of array?(y/n)");
                scanf("%c",&ch);
                while(ch!='y' && ch!='n')
                {
                    printf("\nPlease enter a valid option!");
                    scanf("%c",&ch);
                }
                if(ch=='y')
                {
                    display(1);
                }
                else
                {
                    display(0);
                }
            }
        }
    }
    while(ch!=5);
    return 0;
}
