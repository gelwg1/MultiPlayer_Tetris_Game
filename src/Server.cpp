

int Server::Server(int PORT)
{
    int index=0;
    // TcpSocket socket[5];
    vector <unique_ptr<TcpSocket>> socket;
    socket.push_back(make_unique<TcpSocket>());

    TcpListener listener;
    string mess;

    cout<<"listening"<<endl;
    listener.listen(7000);
    listener.setBlocking(false);
    Packet packet;

    RenderWindow window(VideoMode(320, 100), "Game Server");
    window.setFramerateLimit(50);
    Event e;

    while (window.isOpen())
    {
    	while (window.pollEvent(e))
    	{
    	    if (e.type == Event::Closed)
    		window.close();

            else if(e.type==Event::TextEntered)
        	{
                if (e.text.unicode == 13 && index>0)
                {
                    packet<<mess;
                    for (int j=0; j<index; j++)
                    {
                		socket[j]->send(packet);
                        mess.clear();
                    }
                }
                else mess.push_back(e.text.unicode);
        	}
    	}
        if (listener.accept(*socket[index]) == Socket::Done)
        {
            cout<< "Connected to a new client"<<endl;
            socket[index]->setBlocking(false);
            socket.push_back(make_unique<TcpSocket>());
            index++;
        }
        if (index>0)
        for (int j=0; j<index; j++)
        {
            Socket::Status status = socket[j]->receive(packet);
    		if (status == Socket::Done)
    		{
                cout<<"received message: ";
                packet>>mess;
                cout<<mess<<endl;
                mess.clear();
    		}
            else if (status == Socket::Disconnected)
            {
                cout<<"a user disconnected "<<endl;
                socket.erase (socket.begin()+j);
                index--;
            }
        }
        window.clear(Color::White);
        window.display();
    	usleep(200);
    }

	return 0;
}
