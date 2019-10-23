import java.util.*

public class Main()
{
	int n; 
	public Main(int x)
	{
		n = x;
	}

	void solve()
	{
		int a[][] = new int[n][n];
		int b[][] = new int[n][n];
		int c[][] = new int[n][n];

		boolean d[] = new int[n];
		boolean e[] = new int[2*n-1];
		boolean f[] = new int[2*n-1];

		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				b[i][j] = i+j;
				c[i][j] = i-j+n-1;
			}
		}

		if(process(a,0,b,c,d,e,f)==false)
		{
			System.out.println("no solution");
		}
		else
		{
			for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				System.out.println(a[i][j]);
			}
		}

		}

	}

	public boolean process(int a[][],int col,int b[][],int c[][], int d[],int e[],int f[])
	{
		if(col>=n)
			return true;

		for(int i=0;i<n;i++)
		{
			if(isSafe(i,col,b,c,d,e,f))
			{
				a[i][col]=1;
				e[b[i][col]]=true;
				f[c[i][col]] = true;
				d[i] = true;
				if(process(a,col+1,b,c,d,e,f))
					return true;
				a[i][col]=0;
				e[b[i][col]]=false;
				f[c[i][col]] = false;
				d[i] = false;
			}

		}
		return false;
	}

	public boolean isSafe(int i,int col,int b[][],int c[][], int d[],int e[],int f[])
	{
		if(e[b[i][col]]=true ||
				f[c[i][col]] = true||
				d[i] = true)
			return false;
		return true;
	}

	public static void main(String[]argv)
	{
		//Scanner sc = new Scanner
		Main s = new Main(4);
		s.solve();
	}
}