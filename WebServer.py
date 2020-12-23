from http.server import HTTPServer, BaseHTTPRequestHandler

#in order to use this server, run it and search for 127.0.0.1:2021 in google

class helloHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('content-type', 'text/html')
        self.end_headers()

        self.wfile.write('Hello world!'.encode())


def main():
    PORT = 2021
    server = HTTPServer(('', PORT), helloHandler)
    print('Sever running on port %s' % PORT)
    server.serve_forever()


if __name__ == "__main__":
    main()