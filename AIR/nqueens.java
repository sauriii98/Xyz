import java.util.*;

public class nQueens
{
	static int[][] board;
	static int N;
	
	static Scanner sc = new Scanner(System.in);
	
	static boolean isSafe(int row, int col)
	{
		for(int i=0; i<col; i++)//row
			if(board[row][i] == 1)
				return false;
				
		for(int i=row, j=col; i>=0 && j>=0; i--, j--)
			if(board[i][j] == 1)
				return false;
				
		for(int i=row, j=col; i<N && j>=0; i++, j--)
			if(board[i][j] == 1)
				return false;
				
		return true;
	}
	static boolean process(int col)
	{
		if(col >= N)
			return true;
		
		for(int i=0; i<N; i++)
		{
			if(isSafe(i, col))
			{
				board[i][col] = 1;
				if(process(col+1))
					return true;
				board[i][col] = 0;
			}
		}
		
		return false;
	}
	static boolean solve()
	{
		if(process(0) == true)
		{
			for(int i=0; i<N; i++)
			{
				for(int j=0; j<N; j++)
				{
					System.out.print(board[i][j] + " ");
				}
				System.out.println();
			}
		}
		else
		{
			System.out.println("Solution does Not Exist");
			return false;
		}
		return true;
	}
	public static void main(String args[])
	{
		System.out.println("Enter N: ");
		N = sc.nextInt();
		
		board = new int[N][N];
		
		solve();
	}
}
