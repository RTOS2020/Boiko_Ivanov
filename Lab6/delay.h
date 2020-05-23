void delay(int ms) {
    for (int i = 0; i < 5000 * ms; i++) {
    	__NOP();
    }
}