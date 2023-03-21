package main.java.com.beverageStore.factory;

public class FruitJuice extends BeverageStore {

	@Override
	Beverage createBeverage(String item) {
		// TODO Auto-generated method stub
		if(item.equals("StrawberryJuice")) {
			return new StrawberryJuice();
		}
		else if(item.equals("MangoJuice")) {
			return new MangoJuice();
		}
		else if(item.equals("WatermelonJuice")) {
			return new WatermelonJuice();
		}
		else {
			return null;
		}
	}

}
