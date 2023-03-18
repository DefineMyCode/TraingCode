//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <cstring>
//using namespace std;
//
//int dp[20005];
//int n[1005], v[20005];
//
//int main() {
//    int a, b;
//    while (cin >> a >> b) { // 注意 while 处理多个 case
//        for (int i = 1; i <= b; i++) {
//            cin >> n[i] >> v[i];
//        }
//        //i物品
//        for (int i = 1; i <= b; i++) {
//            //j背包当前体积
//            for (int j = a; j >= 1; j--) {
//                //能放下
//                if (j >= n[i]) {
//                    //物品i时背包容量为j时背包内物品的最大价值
//                    //dp[j]=max(dp[j],dp[j-n[i]]+v[i])
//                    dp[j] = max(dp[j], dp[j - n[i]] + v[i]);
//                }
//
//            }
//        }
//        cout << dp[a] << endl;
//        memset(dp, 0, sizeof(dp));
//    }
//    return 0;
//}