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
//    while (cin >> a >> b) { // ע�� while ������ case
//        for (int i = 1; i <= b; i++) {
//            cin >> n[i] >> v[i];
//        }
//        //i��Ʒ
//        for (int i = 1; i <= b; i++) {
//            //j������ǰ���
//            for (int j = a; j >= 1; j--) {
//                //�ܷ���
//                if (j >= n[i]) {
//                    //��Ʒiʱ��������Ϊjʱ��������Ʒ������ֵ
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