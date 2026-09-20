using System;

class Program {
    static void Main() {
        int r = 3, c = 3;
        int[,] TwoDArr = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        int[] arr = new int[9];

        
        for (int x = 0; x < c; x++) {
            for (int y = 0; y < r; y++) {
                int k = x * r + y;
                arr[k] = TwoDArr[y, x];
            }
        }

        Console.WriteLine("Los elementos del array bidimensional son:");
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                Console.Write(TwoDArr[i, j] + " ");
            }
            Console.WriteLine();
        }

        
        Console.WriteLine("\nLos elementos del array unidimensional son:");
        for (int x = 0; x < r * c; x++) {
            Console.Write(arr[x] + " ");
        }
        Console.WriteLine();
    }
}