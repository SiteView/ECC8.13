package com.siteview.server.xmtp;

import org.jivesoftware.smack.filter.PacketFilter;
import org.jivesoftware.smack.packet.Message;
import org.jivesoftware.smack.packet.Packet;

public class SiteViewPacketFilter implements PacketFilter {

	@Override
	public boolean accept(Packet packet) {
		if(packet instanceof Message)
		{
			return true;
		}
		return false;
	}

}
