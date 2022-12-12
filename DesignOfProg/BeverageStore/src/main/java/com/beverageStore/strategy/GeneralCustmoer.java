package main.java.com.beverageStore.strategy;

public class GeneralCustmoer extends Member {

	public GeneralCustmoer() {
		gift = new HasNoGift();
		discount = new GeneralCustmoerDiscount();
		setRank("GeneralCustmoer");
	}
}
