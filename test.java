class test {
    public static void main(String[] args) {
        
        String b = "he";
        Object c = (Object)b;
        c.getClass();
        System.out.println("hej");

        Object k = new Object();
        k = b;
        k.toString();
        System.out.println(k.toString());
    }
}