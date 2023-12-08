import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Arv arv = new Arv();
        Random random = new Random();
        for(int i=0;i<100;i++){
            arv.insere(random.nextInt(1000) + 1);
        }
        arv.inOrdem();
    }
}