void rmatsub(double p[][100], double q[][100], double r[][100], int m) 
{
    int i, j;
    for (i = 0; i < m; i++) 
    {
        for (j = 0; j < m; j++) 
        {
            r[i][j] = p[i][j] - q[i][j];
        }
    }
}
