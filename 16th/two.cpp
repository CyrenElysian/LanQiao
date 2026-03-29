# include <bits/stdc++.h>
using namespace std;

int chess[7][7];
int row_black[7],row_white[7];
int column_black[7],column_white[7];
vector<string> rows,columns;

void initial()
{
    for(int i=1;i<=6;i++)
    {
        for(int j=1;j<=6;j++)
            chess[i][j]=-1;
    }
    chess[1][1]=chess[5][3]=chess[5][6]=chess[6][5]=1;
    chess[1][2]=chess[1][4]=chess[2][4]=chess[3][5]=chess[3][6]=chess[6][2]=0;

    for(int i=1;i<=6;i++)
    {
        for(int j=1;j<=6;j++)
        {
            if(chess[i][j]==0)
            {
                row_white[i]++;
                column_white[j]++;
            }
            if(chess[i][j]==1)
            {
                row_black[i]++;
                column_black[j]++;
            }
        }
    }
}

bool check_row(int r) // 填满一行时检查
{
    // 黑白棋数量检查
    if(row_black[r]!=3 || row_white[r]!=3) return false;
    // 黑白棋连续性检查
    for(int i=1;i<=4;i++)
    {
        if(chess[r][i]==chess[r][i+1] && chess[r][i+1]==chess[r][i+2]) return false;
    }
    // 不重复性检查
    string s;
    for(int i=1;i<=6;i++) s+=chess[r][i]+'0';
    for(int i=0;i<r;i++) if(rows[i]==s) return false;
    return true;
}

bool check_column(int c)
{
    // 黑白棋数量检查
    if(column_black[c]!=3 || column_white[c]!=3) return false;
    // 黑白棋连续性检查
    for(int i=1;i<=4;i++)
    {
        if(chess[c][i]==chess[c][i+1] && chess[c][i+1]==chess[c][i+2]) return false;
    }
    string s;
    for(int i=1;i<=6;i++) s+=chess[i][c]+'0';
    for(int i=0;i<c;i++) if(columns[i]==s) return false;
    return true;
}

// 实时检查行填充是否合法，每填一次，进行一次检查
bool check_row_ok(int r, int c) // 只检查到c列
{
    if (row_black[r] > 3 || row_white[r] > 3) return false;
    int cnt = 1;
    for (int i = 1; i+1 <= c; i++)
    {
        if (chess[r][i] == chess[r][i+1])
        {
            cnt++;
            if (cnt > 2) return false;
        }
        else cnt = 1;
    }
    return true;
}

bool check_col_ok(int c,int r) // 只检查到r行
{
    if (column_black[c] > 3 || column_white[c] > 3) return false;
    int cnt = 1;
    for (int i = 1; i+1 <= r; i++)
    {
        if (chess[i][c] == chess[i+1][c])
        {
            cnt++;
            if (cnt > 2) return false;
        }
        else cnt = 1;
    }
    return true;
}

bool dfs(int pos)  // 从上到下，从左到右遍历
{
    if(pos==36)
    {
        for(int i=1;i<=6;i++)
        {
            if(!check_row(i) || !check_column(i)) return false;
        }
        return true;
    }

    int r=(pos/6)+1,c=(pos%6)+1;
    if (chess[r][c]!=-1) return dfs(pos+1);

    for(int val=0;val<=1;val++)
    {
        chess[r][c]=val;
        if(val==0)
        {
            row_white[r]++;
            column_white[c]++;
        }
        else
        {
            row_black[r]++;
            column_black[c]++;
        }

        // 依次检查
        bool ok= true;
        // 检查行棋子数，连续情况
        if(!check_row_ok(r,c)) ok= false;
        // 检查列棋子数，连续情况
        if(!check_col_ok(c,r)) ok= false;
        // 检查行重复情况
        if(ok && c==6)
        {
            if(!check_row(r)) ok= false;
        }
        else
        {
            string s;
            for(int i=0;i<6;i++) s+=chess[r][i]+'0';
            rows.push_back(s);
        }
        // 检查列重复情况
        if(ok && r==6)
        {
            if(!check_column(c)) ok= false;
        }
        else
        {
            string s;
            for(int i=0;i<6;i++) s+=chess[i][c]+'0';
            columns.push_back(s);
        }

        // 关键一步，若之前均ok，检查下一个pos，所有pos均ok返回true
        if(ok && dfs(pos+1)) return true;

        // 若之前某步骤存在不ok，递归回溯
        if(val==0)
        {
            row_white[r]--;
            column_white[c]--;
        }
        else
        {
            row_black[r]--;
            column_black[c]--;
        }
        // 遍历到最后一列或最后一行，pop之前push的字符串
        if(c==6) rows.pop_back();
        if(r==6) columns.pop_back();
        chess[r][c]=-1;
    }
    return false;
}

int main()
{
    initial();

    if(dfs(0))
    {
        for(int i=1;i<=6;i++)
        {
            for(int j=1;j<=6;j++)
            {
                cout<<chess[i][j];
            }
        }
    }
}