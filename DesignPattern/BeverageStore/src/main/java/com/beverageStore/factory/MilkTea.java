package main.java.com.beverageStore.factory;

public class MilkTea extends BeverageStore {

	@Override
	Beverage createBeverage(String item) {
		// TODO Auto-generated method stub
		if(item.equals("HongKongMilkTea")) {
			return new HongKongMilkTea();
		}
		else if(item.equals("MatchaMilkTea")) {
			return new MatchaMilkTea();
		}
		else if(item.equals("WheatFragrantMilkTea")) {
			return new WheatFragrantMilkTea();
		}
		else {
			return null;
		}
	}

}
