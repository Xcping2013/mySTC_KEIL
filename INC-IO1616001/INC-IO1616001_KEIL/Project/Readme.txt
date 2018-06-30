iic 写AT24128		ACK、ACK.....     STOP
iic 读AT24128       ACK、ACK...NO ACK STOP

20170628--Ver4.0:	修改Power off命令---只断VBUS,不断地线  防止Power Off到Power on时读取不到开机提示（乱码干扰）

