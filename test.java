import java.util.ArrayList;
import java.util.List;

class test {
    public static void main(String[] args) {
        Object temp = new Object();
        
        System.out.println(ninetyone(10));

        synchronized(temp) {
            synchronized(temp) {
                int i;
            }
        }
    }

    static int ninetyone (int x){
        if (x>100)
            return x-10;
        else
            return ninetyone(ninetyone(x+11));
    }
}