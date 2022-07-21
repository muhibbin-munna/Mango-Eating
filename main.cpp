#include<bits/stdc++.h>
using namespace std;


int n;
int mango[100];
int dp[100];
int pos[100];

void initialize()
{
    for(int i=0; i<100; i++)
    {
        mango[i] = dp[i] = 0;
        pos[i] = -1;
    }
}

void countPos()
{
    int postSum = 0;
    dp[n-1] = mango[n-1];
    postSum = mango[n-1];
    pos[n-1] = n-1;

    /*cout<<"\nMango : ";
    for (int i=0; i<n; i++)
        cout<< mango[i]<< " ";
    cout<<"\ndp : ";
    for (int i=0; i<n; i++)
        cout<< dp[i]<< " ";
    cout<< "\npostSum : " << postSum;
    cout<<"\npos : ";
    for (int i=0; i<n; i++)
        cout<< pos[i]<< " ";
    cout<<"\n";*/


    for(int i= n-2; i>=0; i--)
    {
        dp[i] = max(dp[i+1],
                    mango[i] + postSum - dp[i+1]);
        if((mango[i] + postSum - dp[i+1])>dp[i+1])
        {
            pos[i] = i;
        }
        else
        {
            pos[i] = pos[i+1];
        }

        postSum += mango[i];

        /*cout<< "\npostSum : " << postSum;

        cout<<"\ndp : ";
        for (int i=0; i<n; i++)
            cout<< dp[i]<< " ";
        cout<<"\npos : ";
        for (int i=0; i<n; i++)
            cout<< pos[i]<< " ";
        cout<<"\n"; */
    }
}

void showBox()
{

    for(int i=0; i<13; ++i)
        cout<<" ";

    for(int i=1; i<=5*n; ++i)
    {
        cout<<"_";
    }
    cout<<endl;
    cout<<"Box Number  |";
    for(int i=0; i<n; ++i)
    {
        printf("%4d|",i+1);
    }
    cout<<endl;

    for(int i=0; i<12; ++i)
        cout<<" ";
    cout<<"|";
    for(int i=1; i<=5*n; ++i)
    {
        if(i%5==0)
            cout<<"|";
        else
            cout<<"_";
    }
    cout<<endl;

    cout<<"Mango       |";
    for(int i=0; i<n; ++i)
    {
        printf("%4d|",mango[i]);
    }
    cout<<endl;
    for(int i=0; i<12; ++i) cout<<" ";
    cout<<"|";
    for(int i=1; i<=5*n; ++i)
    {
        if(i%5==0)
            cout<<"|";
        else
            cout<<"_";
    }
    cout<<endl;

}


void showResult(int &playerScore, int &aiScore)
{
    if(playerScore>aiScore)
    {
        cout<<"Player wins"<<endl;
    }
    else if(playerScore < aiScore)
    {
        cout<<"AI wins"<<endl;
    }
    else
    {
        cout<<"Match Drawn"<<endl;
    }
    cout<<endl<<endl;
}


int main()
{
    while(1)
    {
label_1:
        initialize();
        cout<<"Enter the number of box filled with mango : ";
        cin>>n;
        srand(time(NULL));
        int v1=rand()%50;
        for(int i=0; i<n; i++)
        {
            mango[i]=(rand()%501)%v1+1;
        }

        countPos();
        showBox();
        int playerScore = 0, aiScore = 0, nextOfAI = -1, index=-1;

        while(1)
        {
label_2:
            cout<<"Enter the index : ";
            cin>>index;
            if(index<1 || index>n)
            {
                cout<<"Index out of range"<<endl<<endl;
                showBox();
                goto label_2;
            }

            index = index -1;

            playerScore = playerScore + mango[index];
            mango[index] = 0;
            for(int i = nextOfAI+1; i<index; i++)
            {
                aiScore = aiScore + mango[i];
                mango[i] = 0;
            }

            cout<<"Player in : "<<index+1<<endl;
            cout<<"Player score : "<<playerScore<<endl;
            cout<<"AI score : "<<aiScore<<endl<<endl;

            nextOfAI = pos[index+1];

            if(nextOfAI == -1)
            {
                showResult(playerScore, aiScore);
                goto label_1;
            }

            aiScore = aiScore + mango[nextOfAI];
            mango[nextOfAI] = 0;

            for(int i = index+1; i<nextOfAI; i++)
            {
                playerScore = playerScore + mango[i];
                mango[i] = 0;
            }

            cout<<"AI in : "<<nextOfAI+1<<endl;
            cout<<"AI score : "<<aiScore<<endl;
            cout<<"Player score : "<<playerScore<<endl<<endl;

            if(nextOfAI>=n-1)
            {
                showResult(playerScore, aiScore);
                break;
            }
            cout<<endl;
            showBox();
        }


    }

    return 0;
}
