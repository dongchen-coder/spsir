int goodnight() {
	int a[10];
	int sum = 0;
	for (int i = 0; i < 10; i++) {
		a[i] = i;
		sum += a[i];
	}
	return sum;
}
