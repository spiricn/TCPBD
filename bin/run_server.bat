:loop

tcpbd_server.exe %1 %2

echo "Server crashed, respawning..."

timeout /t 5 /nobreak > NUL

goto loop
