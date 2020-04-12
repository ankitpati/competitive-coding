import java.util.List;
import java.util.ArrayList;

class CoinChange {
    static int doit(int N, List<Integer> C) {
        int[] memo = new int[N + 1];
        memo[0] = 1;

        int listSize = C.size();

        for (int i = 0; i < listSize; ++i) {
            int coinValue = C.get(i);

            for (int j = 0; j <= N; ++j) {
                if (coinValue <= j) {
                    memo[j] += memo[j - coinValue];
                }
            }
        }

        return memo[N];
    }

    public static void main(String[] args) {
        ArrayList<Integer> al = new ArrayList<>();
        al.add(1);
        al.add(2);
        al.add(3);

        System.out.println(doit(4, al));
    }
}
