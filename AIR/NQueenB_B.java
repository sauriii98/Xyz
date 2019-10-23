public class NQueenB_B 
{	
	public static int N = 8;
	
	static boolean isSafe(int row,int col,int[][] b,int[][] c,boolean[] d,boolean[] e,boolean[] f)
	{
		if(e[b[row][col]]|| f[c[row][col]] || d[row])
			return false;
		return true;
	}
	static boolean solveNQueenUtil(int[][] a,int col,int[][] b,int[][] c,boolean[] d,boolean[] e,boolean[] f)
	{
		if(col>=N)
			return true;
		for(int i=0;i<N;i++)
		{
			if(isSafe(i,col,b,c,d,e,f))
			{
				a[i][col]=1;
				d[i]=true;
				e[b[i][col]]=true;
				f[c[i][col]]=true;
			
				if(solveNQueenUtil(a,col+1,b,c,d,e,f))
					return true;
			
				a[i][col]=0;
				d[i]=false;
				e[b[i][col]]=false;
				f[c[i][col]]=false;
			}	
		}
		return false;
	}
	static void printSol(int[][] a)
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				System.out.print(a[i][j]+"  ");
			}
			System.out.println();
		}
	}
	static boolean solveNQueens()
	{
		int[][]  a = new int[N][N];
		int[][]  b = new int[N][N];
		int[][]  c = new int[N][N];
		
		boolean[] d = new boolean[N];
		boolean[] e = new boolean[2*N-1];
		boolean[] f = new boolean[2*N-1];
		
		for(int r=0;r<N;r++)
		{
			for(int c=0;c<N;c++)
			{
				b[r][c] = r+c;
				c[r][c] = r-c+(N-1);
			}
		}
		
		if(solveNQueenUtil(a,0,b,c,d,e,f)==false)
		{
			System.out.println("Solution does not exist");
			return false;
		}
		printSol(a);
		return true;
	}	
	public static void main(String[] args)
	{
		solveNQueens();
	}
}
