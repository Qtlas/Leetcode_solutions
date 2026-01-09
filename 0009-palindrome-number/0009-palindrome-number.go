func isPalindrome(x int) bool {
    if x < 0 {return false}
    n, temp := 0, x
    for n < temp && x!= 0 {
        n = n*10 + x % 10
        x = x/10
    }
    return n==temp
 }