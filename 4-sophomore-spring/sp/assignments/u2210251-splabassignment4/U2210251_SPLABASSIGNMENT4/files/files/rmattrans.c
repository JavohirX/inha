void rmattrans(double p[][100], double r[][100], int m) 
{
    int i, j;
    for (i = 0; i < m; i++) 
    {
        for (j = 0; j < m; j++) 
        {
            r[j][i] = p[i][j];
        }
    }
}
