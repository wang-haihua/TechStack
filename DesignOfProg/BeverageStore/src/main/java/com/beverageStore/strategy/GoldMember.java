package main.java.com.beverageStore.strategy;

public class GoldMember extends Member {

	public GoldMember() {
		gift = new HasNoGift();
		discount = new GoldMemberDiscount();
		setRank("GoldMember");
	}
}
