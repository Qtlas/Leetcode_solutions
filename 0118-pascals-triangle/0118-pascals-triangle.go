func generate(numRows int) [][]int {
    pascal := [][]int{};
	
	for i:=0; i<numRows; i++ {
		temp := make([]int, i+1);
		temp[0] = 1;
		temp[i] = 1;

		for j:=1; j<i; j++ {
			temp[j] = pascal[i-1][j-1] + pascal[i-1][j];
		}

		pascal = append(pascal, temp);
	}

    return pascal;
}
	
	