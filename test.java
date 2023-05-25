class test {
    public static void main(String[] args) {
     
        
    }

    int sum(int n) {
        if (n == 0) return 0;
        return n + sum(n-1);
    }

    int sum(int n, int acc) {
        if (n == 0) return acc;
        return sum(n-1, acc + n);
    }

}
class B {
    void test(Integer b, String c) { System.out.println(c);}
    void test(String c, Integer b) { System.out.println(c);}
}