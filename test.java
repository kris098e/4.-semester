class test {
    public static void main(String[] args) {
        
        Number[] numbers = new Number[]{1, 2, 3};
        numbers[2] = new Integer(2);

        Number b = numbers[2];
        System.out.println(b);
    }
}