# RKB

Remote keyboard.

Used to send keystrokes to remotely connected devices over [socket.io](https://socket.io/).

Supported OS:
- Windows

## Sender

```
> rkb send <server_address> <port>
```

## Receiver

```
> rkb receive <server_address> <port>
```

## Server

Host a [server](https://github.com/szclsb/rkeyboard-server) on `<server_address>` with port `<port>`.