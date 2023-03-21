package main.java.com.beverageStore.strategy;

public class PlatinumMember extends Member {

	public PlatinumMember() {
		gift = new HasGift();
		discount = new PlatinumMemberDiscount();
		setRank("PlatinumMember");
	}
}
