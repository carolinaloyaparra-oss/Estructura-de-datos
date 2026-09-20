public class Practica1 {
    public static void main(String[] args) {
        int r = 3, c = 3;
        int[][] twoDArr = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        int[] arr = new int[9];

    
        for (int x = 0; x < c; x++) {
            for (int y = 0; y < r; y++) {
                int k = x * r + y;
                arr[k] = twoDArr[y][x];
            }
        }

   
        System.out.println("Los elementos del array bidimensional son:");
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                System.out.print(twoDArr[i][j] + " ");
            }
            System.out.println();
        }

       
        System.out.println("\nLos elementos del array unidimensional son:");
        for (int x = 0; x < r * c; x++) {
            System.out.print(arr[x] + " ");
        }
        System.out.println();
    }
}