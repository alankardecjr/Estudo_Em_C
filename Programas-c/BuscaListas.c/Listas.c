int busca_binaria ( int lista [ ] , int elemento , int inicio , int fim ) {
2 		int meio = floor ( ( fim + inicio ) / 2 );
3 		if ( ( inicio == fim ) && ( lista [ meio ] != elemento ) )
4 			return -1;
5 		else if ( lista [ meio ] == elemento )
6 			return meio;
7 		else if ( elemento < lista [ meio ] )
8 			busca_binaria ( lista , elemento , inicio , meio );
9 		else busca_binaria ( lista , elemento , meio + 1 , fim );
10 	}
