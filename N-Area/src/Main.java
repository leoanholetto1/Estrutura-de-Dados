import java.util.Random;

public class Main {
    public static void main(String[] args) {
        NArea area = new NArea();

        Random random = new Random();
        for(int i=0;i<100;i++){
            area.inserir(i);
        }
        for(int i=110;i>100;i--){
            area.inserir(i);
        }
        for(int i=400;i>150;i--){
            area.inserir(i);
        }
        for(int i=500;i<1000;i++){
            area.inserir(i);
        }


       for(int i=0;i<10;i++){
           int valor = random.nextInt(100);
           System.out.println(valor);
           area.exclusao(valor);
       }




        area.exibe();

    }
}