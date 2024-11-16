#include<bits/stdc++.h>

#define ll long long
#define matrix vector<vector<ll>> 
const int MOD = 1e9 + 7;
using namespace std;


// PROGRAM FOR GETTING THE LOWEST PRIME FACTOR OF A NUMBER
// const int MAX_N=5e6 + 10;
// bool mark[MAX_N];
// int gtPrime[MAX_N];
// long long fn[MAX_N];

// void init(){
//     for (int i=2; i<MAX_N; i++){
//         if (!mark[i]){
//             gtPrime[i]=i;
//             for (int j=i+i; j<MAX_N; j+=i){
//                 mark[j]=1;
//                 gtPrime[j]=i;
//             }
//         }
//     }
//     fn[1]=0;
//     for (int i=2; i<MAX_N; i++) fn[i] = fn[i/gtPrime[i]]+1;
//     for (int i=2; i<MAX_N; i++) fn[i] += fn[i-1];
// }


/* Namespace for PDS */
// using namespace __gnu_pbds;
// template <typename T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


// double getMedian(ordered_set<pair<ll,int>> &st, int k){
//     if (k&1){
//         return (double)st.find_by_order((k-1)/2)->first;
//     }
//     return (double)(st.find_by_order((k-1)/2)->first + st.find_by_order(k/2)->first) / 2.0;
// }

// 
// extended gcd 
long long egcd(long long a, long long b, long long &px, long long &py){
    long long x=0; px=1;
    long long y=1; py=0;
    while (b){
        int q=a/b;
        long long tx=x, ty=y;
        x = px-q*x;
        y = py-q*y;
        px=tx;
        py=ty;
        long long tmp=a%b;
        a=b;
        b=tmp;
    }
    return a;
}

bool isPrime(ll n){
    if (n <= 1) return false;
    if (n <= 3) return true;

    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (ll i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}

int countPrimeFactors(int n){
    int ans=0;
    while (n%2 == 0){
        ans++;
        n >>= 1;
    }
    for (int i=3; i*i<=n; i+=2){
        while (n % i == 0){
            ans++;
            n = n/i;
        }
    }
    if (n>2){
        ans++;
    }
    return ans;
}

bool isPalin(int n){
    string num=to_string(n);
    int l=0, r=num.size()-1;
    while (l<r){
        if (num[l++] != num[r--]) return false;
    }
    return true;
}

matrix matrixMult(matrix &A, matrix &B){
    int n = A.size();
    matrix C = matrix(n, vector<ll>(n));
    
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            C[i][j] = ((A[i][0] * B[0][j]) % MOD + (A[i][1] * B[1][j]) % MOD) % MOD;
        }
    }
    return C;
}

matrix fibPower(matrix &M, int n){
    if (n==1){
        return M;
    }
    matrix half = fibPower(M, n/2);
    matrix ans = matrixMult(half, half);
    if (n & 1){
        ans = matrixMult(ans, M);
    }
    return ans;
}

int FindNthTerm(long long int n) {
    if (n <= 1){
        return n;
    }
    matrix M = {{1,1},{1,0}};
    return fibPower(M, n)[0][0];
}

void printMatrix(matrix a){
    int n = a.size();
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

// sign = -1 if considering count that meet values in nums 
// sign = 1 if NOT considering count that meet values in nums
int inc_exc(int idx, int d, int sign, const int n, vector<int> &nums){
    if (idx == nums.size()){
        // comment next line if NOT considering values in nums
        if (d==1) return 0; // nothing selected 
        return sign*n/d;
    }
    return inc_exc(idx+1, d, sign, n, nums) + inc_exc(idx+1, lcm(d, nums[idx]), sign*-1, n, nums);
}
/*
const int N=600;
    
    string s1, s2;
    while (cin >> s1 >> s2){
        int a[N] = {};
        reverse(s1.begin(), s1.end());
        reverse(s2.begin(), s2.end());
        
        for (int i=0; i<s1.size(); i++){
            for (int j=0; j<s2.size(); j++){
                a[i+j] += (s1[i]-'0')*(s2[j]-'0');
            }
        }
        for (int i=0; i<N-1; i++){
            a[i+1] += a[i]/10;
            a[i] %= 10;
        }
        int i=N-1;
        while (i>0 && a[i]==0) i--;
        for (; i>=0; i--){
            cout << a[i];
        }
*/

string tradMul(string &s1, string &s2){
    if (s1=="0" || s2=="0"){
        return s1;
    }
    int n1=s1.size(), n2=s2.size();
    if (n2 > n1) {
        swap(n1, n2);
        swap(s1, s2);
    }
    string ans = string(n1+n2, '0');
    int carry,tmp;
    for (int i=n1-1; i>=0; i--){
        carry=0;
        for (int j=n2-1; j>=0; j--){
            tmp = (s1[i]-'0') * (s2[j]-'0') + (ans[i+j+1]-'0') + carry;
            ans[i+j+1] = '0' + (tmp%10);
            carry = tmp/10;
        }
        ans[i] += carry;
    }
    for (int i=0; i<n1+n2; i++){
        if (ans[i] != '0') return ans.substr(i);
    }
    return "0";
}

string addStrings(string &num1, string &num2) {
    string ans;
    int carry=0, tmp;
    int n1=num1.size(), n2=num2.size();
    int i=n1-1, j=n2-1;
    while (i >= 0 || j>=0 || carry){
        tmp = carry;
        tmp += i >=0 ? num1[i--]-'0' : 0;
        tmp += j >= 0 ? num2[j--]-'0' : 0;
        ans += '0' + (tmp%10);
        carry = tmp/10;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

/*
The assumption is that s1 >= s2 
*/
string subString(string &s1, string &s2){
    if (s2 == "0") return s1;
    if (s1 == s2) return "0";

    int i=s1.size()-1, j=s2.size()-1;
    int flag=0, x,y;
    string ans;

    while (i >= 0 || j>=0){
        y = (j>=0) ? s2[j--]-'0' : 0;
        x = (i>=0) ? s1[i--]-'0' : 0;
        if (flag) x--, flag=0; // borrowed from previous operation
        if (x < y){
            x += 10;
            flag=1;
        }
        ans += '0' + (x-y);
    }
    while (ans.size() && ans.back()=='0') ans.pop_back();
    reverse(ans.begin(), ans.end());
    return ans.size() ? ans : "0";
}

string karatsuba(string s1, string s2){
    int n1=s1.size(), n2=s2.size();
    if (n1==1 || n2==1){
        return tradMul(s1, s2);
    }
    int mid=max(n1,n2)/2;
    string h1 = s1.substr(0, mid), l1=s1.substr(mid);
    string h2 = s2.substr(0, mid), l2=s2.substr(mid);

    string l1h1 = addStrings(l1, h1), l2h2=addStrings(l2, h2);

    string z0 = karatsuba(l1, l2);
    string z1 = karatsuba(l1h1, l2h2);
    string z2 = karatsuba(h1, h2);

    // (z1 - z2 - z0)*10^mid 
    string z1z2 = subString(z1, z2); 
    string z1z2z0 = subString(z1z2, z0);
    z1z2z0 += string(mid, '0');
    cout << z1z2z0 << " " << endl;

    // z2*10^(mid*2)
    z2 += string(mid*2, '0');
    string ans = addStrings(z2, z1z2z0);
    return addStrings(ans, z0);
}

int main(){
    string s1 = "1234", s2="5678";
    cout << karatsuba(s1, s2) << "\n";
}
