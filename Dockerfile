FROM gcc:latest
WORKDIR /app
COPY Vaja2/main.cpp .
RUN g++ -o program main.cpp
ENTRYPOINT ["./program"]