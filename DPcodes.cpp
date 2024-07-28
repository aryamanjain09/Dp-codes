
// recursive knapsack code
int knapsack_recursion(int wt[], int val[], int n, int w) // n is size of wt
{
    if (n == 0 || w == 0)
    {
        return 0;
    }
    if (wt[n - 1] <= w)
    {
        return max((val[n - 1] + knapsack_recursion(wt, val, n - 1, w - wt[n - 1])), knapsack_recursion(wt, val, n - 1, w));
    }
    else
    {
        return knapsack_recursion(wt, val, n - 1, w);
    }
}
// tabulation knapsack code
// change n,w to i,j and apply for loop. no changes made to if else
vector << vector < int >> dp(n, vector<int>(n, 0));
int knapsack_tabulation(int wt[], int val[], int n, int w, vector << vector < int >> &dp) // n is size of wt
{
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 1; j < w + 1; j++)
        {
            if (i == 0 || j == 0)
            {
                dp[i][j] = 0;
            }
        }
    }
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < w + 1; j++)
        {
            if (wt[i - 1] <= j)
                j
                {
                    dp[i][j] = max((val[i - 1] + dp[i - 1][j - wt[i - 1]]), dp[i - 1][j]);
                }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[i][j];
}
// unbounded knapsack code - multiple occurences of a same item is allowed - only difference is in pick call next function on  index n only,
// dont reduce index to n-1 because u can again choose to take it. but in the not pick call, shift index to n-1, you cant take this after rejecting
int unbounded_knapsack_recursion(int wt[], int val[], int n, int w) // n is size of wt
{
    if (n == 0 || w == 0)
    {
        return 0;
    }
    if (wt[n - 1] <= w)
    {
        return max((val[n - 1] + knapsack_recursion(wt, val, n, w - wt[n - 1])), knapsack_recursion(wt, val, n - 1, w));
    }
    else
    {
        return knapsack_recursion(wt, val, n - 1, w);
    }
}

//subset sum equal to target - recursion
int subsetsum(int n, int target, vector<int> arr)
{
`   if(target==0) return true;
    if(n==0)return arr[0]==target;
    bool pick = false;
    if(arr[n-1]<=target)
    {
        pick = subsetsum(n-1,target-arr[n],arr);
    }
    bool notpick = subsetsum(n-1,target,arr);
    return pick+notpick;
}


//subset sum equal to target - tabulation
bool isSubsetSum(vector<int>s, int target){
    int n = s.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false)); //important - declaring dp in a true/false returning pattern

    // If the target is 0, the answer is true as we can always form 0 sum with an empty subset
    for (int i = 0; i <= n; ++i)
        dp[i][0] = true;

    for (int i = 1; i <= n; ++i) {
        int currentCharValue = s[i - 1]; // ASCII value of the current character
        for (int j = 1; j <= target; ++j) {
            if (j >= currentCharValue)
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - currentCharValue];
            else
                dp[i][j] = dp[i - 1][j]; // means that if we do not pick element at(i,j), the boolean value at dp[i-1][j] is one of our option. 'the boolean value at dp[i-1][j]' tells us that will a string with a character less (i-1) be able to return the target of j?
        }
    }

    return dp[n][target]; 
    }


//Length of longest common subsequence code - recursion and tabulation

// v v v imp - Size of DP array is determined by the input. usually in memoisation it is seen that the input is the index of string, example- index for s1 anges from 
    //0 to n-1 and index for s1 ranges from 0 to m-1 then the DP can be of(n*m) size. 
    //BUT in Tabulation usually input is complete size of string so input ranges from 0 to n and 0 to m. so dp array is of size(n+1 * m+1)

class Solution {
public:
    int recursion_memoisation_lcs(string s1, string s2,int i,int j,vector<vector<int>>& dp)  // done using i and j - indexes of strings
    {
        if(i<0 || j <0)return 0;
        if(dp[i][j]!=-1)return dp[i][j];
        if(s1[i]==s2[j]) 
        {
            return dp[i][j] = 1+func(s1,s2,i-1,j-1,dp);
        }
        return dp[i][j] = max(func(s1,s2,i-1,j,dp),func(s1,s2,i,j-1,dp));
    }
    int tabulation_lcs(string s1, string s2,int n,int m,vector<vector<int>>& dp)
    {
        for(int i = 0;i<=n;i++)
        {
            dp[i][0]=0;
        }
        for(int j = 0;j<=m;j++)
        {
            dp[0][j]=0;
        }
        for(int i = 1;i<=n;i++)
        {
            for(int j = 1;j<=m;j++)
            {
                if(s1[i-1]==s2[j-1]) //v v imp - Since the dp table includes an extra row and column at the beginning to handle base cases, the actual characters in s1 and s2 corresponding to dp[i][j] are at positions i-1 and j-1 in the strings.
                {
                    dp[i][j]=dp[i-1][j-1]+1;
                }
                else{dp[i][j]=max(dp[i-1][j],dp[i][j-1]);}
                
            }
        }
        return dp[n][m];
    }

    int longestCommonSubsequence(string text1, string text2) {   //main() function
        int n=text1.length();
        int m=text2.length();
        //
        vector<vector<int>> dp(n+1,vector<int>(m+1,0)); //for tabulation
        return tabulation_lcs(text1,text2,n,m,dp);//for tabulation 
        //note-for tabulation you can just directly write function code here as well if u need to use the dp table ahead
        //
        vector<vector<int>> dp(n,vector<int>(m,-1)); //for memoisation
        return recursion_memoisation_lcs(text1,text2,n-1,m-1,dp);//for memoisation
    }
};

//Print of longest common subsequence
void longest_common_subsequence(string s1, string s2, int n, int m)
{
        //Dp table generation code
        vector<vector<int>> dp(n+1,vector<int>(m+1,0));

        for(int i = 0;i<=n;i++)
        {
            dp[i][0]=0;
        }
        for(int j = 0;j<=m;j++)
        {
            dp[0][j]=0;
        }

        for(int i = 1;i<=n;i++)
        {
            for(int j = 1;j<=m;j++)
            {
                if(s1[i-1]==s2[j-1])
                {
                    dp[i][j]=dp[i-1][j-1]+1;
                }
                else{dp[i][j]=max(dp[i-1][j],dp[i][j-1]);}
                
            }
        }
 
    // Following code is used to print LCS
    int lcs_length = dp[m][n];
 
    // Create a character array to store the lcs string
    char lcs[lcs_length + 1];
    lcs[index] = '\0'; // Set the terminating character
 
    // Start from the right-most-bottom-most corner and
    // one by one store characters in lcs[]
    int i = m, j = n;
    while (i > 0 && j > 0) {
        // If current character in X[] and Y are same, then
        // current character is part of LCS
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1]= X[i - 1]; // Put current character in result
            i--;
            j--;
            index--; // reduce values of i, j and index
        }

        // If not same, then find the larger of two and
        // go in the direction of larger value
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }
 
    // Print the lcs
    cout << "LCS of " << s1 << " and " << s2 << " is " << lcs;
}

//print of shortest common supersequence
class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int n=str1.length();
        int m=str2.length();
        vector<vector<int>> dp(n+1,vector<int>(m+1,0)); //for tabulation
        for(int i = 0;i<=n;i++)
        {
            dp[i][0]=0;
        }
        for(int j = 0;j<=m;j++)
        {
            dp[0][j]=0;
        }
        for(int i = 1;i<=n;i++)
        {
            for(int j = 1;j<=m;j++)
            {
                if(str1[i-1]==str2[j-1])
                {
                    dp[i][j]=1+dp[i-1][j-1];
                }else{
                    dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                }
                
            }
        }
        string ans = "";
        int i=n;
        int j=m;
        while(i>0 && j>0)
        {
            if(str1[i-1]==str2[j-1])
            {
                ans+=str1[i-1];
                i--;
                j--;<
            }
            else if(dp[i-1][j]>dp[i][j-1])
            {
                ans+=str1[i-1];
                i--;
            }else{
                ans+=str2[j-1];
                j--;
            }
        }
        while(i>0)
        {
            ans+=str1[i-1];
            i--;
        }
        while(j>0)
        {
            ans+=str2[j-1];
            j--;
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};

// LIS longest increasing subsequence 
int LIS_recursion(int ind, int prevind,int n, vector<int>& nums)
{
    if(ind==n)return 0;
    int select = 0;
    if(prevind == -1 || nums[ind]>nums[prevind])//you need to check for 1st run when prevind == -1 
    {
        select = 1 + LIS_recursion(ind+1,ind,nums); //if seected prevind becomes current index
    }
    int notselect = LIS_recursion(ind+1,prevind,nums);
    return max(select,notselect);
}
//ind runs from 0 to n-1. Therefrore we can use n size DP. Prevind runs from -1 to n-1. therefore we can not store it in DP due to -ve index,so we do a coordintate change.
//-1 of prevind is stored at 0 of dp. 0 of prevind is stored at 1 of dp. and so on... Now I require dp of size n+1, starting from 0 to n. so you will use dp[ind][prevind+1]. instead of dp[ind][prevind] to access and store values at the correct location in the dp

//therefore add +1 to prevind
int LIS_memoisation(int ind, int prevind,int n, vector<int>& nums,vector<vector<int>> &dp)
{
    if(ind==n)return 0;
    id (dp[ind][prevind+1] == -1) return dp[ind][prevind+1];
    int select = 0;
    if(prevind == -1 || nums[ind]>nums[prevind])//you need to check for 1st run when prevind == -1 
    {
        select = 1 + LIS_recursion(ind+1,ind,nums,dp); //if selected, prevind becomes current index //note that +1 happens only in dp declaration, not function
    }
    int notselect = LIS_recursion(ind+1,prevind,nums,dp);
    return dp[ind][prevind+1]=max(select,notselect);
}

//in tabulation, ind will go from n-1 to 0 and prevind from n-1 to -1. but prev ind can never be more than ind. so in reality prevind goes from ind-1 to -1
//
int LIS_tabulation(int ind, int prevind,int n, vector<int>& nums,vector<vector<int>> &dp)
{
    //no base case initialisation required because our whole dp is initialised with 0 only
    for(int ind=n-1;ind>=0;ind--)
    {
        for(int prevind=ind-1;prevind>= -1;prevind--)
        {
            int select = 0;
            if(prevind == -1 || nums[ind]>nums[prevind])//you need to check for 1st run when prevind == -1 
            {
                select = 1 + dp[ind+1][prevind+1]; //do +1 to prevind (coordinate shift)
            }
            int notselect = dp[ind+1][prevind+1];
             dp[ind][prevind+1]=max(select,notselect);
        }

    }return dp[0][-1+1];

}
int mainfunction_lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(n,vector<int>(n+1,-1));//memoisation
    vector<vector<int>> dp(n+1,vector<int>(n+1,0));//tabulation

    return LIS_recursion(0,-1,n,nums);
}
