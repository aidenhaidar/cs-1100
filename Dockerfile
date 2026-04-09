FROM gcc:12

WORKDIR /app

# Copy source files
COPY *.cpp *.h Makefile ./

# Build the project
RUN make

# Expose the port (Railway sets PORT env variable)
EXPOSE 8080

# Run the server
CMD ["./guess_the_output"]
