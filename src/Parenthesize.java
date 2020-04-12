import java.util.List;
import java.util.ArrayList;
import java.util.HashMap;

class Parenthesize {
    static HashMap<String, ArrayList<Integer>> memo = new HashMap<>();

    static List<Integer> parenthesize(String expr) {
        ArrayList<Integer> valueList = memo.get(expr);
        if (valueList != null) {
            return valueList;
        }

        valueList = new ArrayList<>();

        int exprLength = expr.length();

        for (int i = 0; i < exprLength; ++i) {
            char currentChar = expr.charAt(i);

            if (currentChar == '+' || currentChar == '-' || currentChar == '*') {
                String pre = expr.substring(0, i);
                String post = expr.substring(i + 1);

                List<Integer> preValueList = parenthesize(pre);
                List<Integer> postValueList = parenthesize(post);

                int preSize = preValueList.size();
                int postSize = postValueList.size();

                for (int j = 0; j < preSize; ++j) {
                    for (int k = 0; k < postSize; ++k) {
                        if (currentChar == '+') {
                            valueList.add(preValueList.get(j) + postValueList.get(k));
                        } else if (currentChar == '-') {
                            valueList.add(preValueList.get(j) - postValueList.get(k));
                        } else {
                            valueList.add(preValueList.get(j) * postValueList.get(k));
                        }
                    }
                }
            }
        }

        if (valueList.size() == 0) {
            if (expr.equals("")) {
                valueList.add(0);
            } else {
                valueList.add(Integer.parseInt(expr));
            }
        }

        valueList.sort((a, b) -> a - b);
        memo.put(expr, valueList);
        return valueList;
    }

    public static void main(String[] args) {
        System.out.println(parenthesize("3-2-1"));
        System.out.println(parenthesize("5*4-3*2"));
    }
}
