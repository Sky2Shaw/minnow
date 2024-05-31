#include "byte_stream.hh"
#include <memory>
#include <queue>
#include <stdexcept>
using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ), buffer( queue<char>() ) {}

bool Writer::is_closed() const
{
  // Your code here.
  return g_isClose;
}

void Writer::push( string data )
{
  // Your code here.
  if ( data.empty() ) {
    return;
  }
  for ( auto c : data ) {
    if ( buffer.size() == capacity_ || g_isClose ) {
      break;
    }

    buffer.push( c );
    g_bytes_pushed++;
  }
  return;
}

void Writer::close()
{
  g_isClose = true;
  // Your code here.
}

uint64_t Writer::available_capacity() const
{

  // Your code here.
  return capacity_ > buffer.size() ? capacity_ - buffer.size() : 0;
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return g_bytes_pushed;
}

bool Reader::is_finished() const
{
  // Your code here.
  return g_isClose and buffer.empty();
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return g_bytes_popped;
}

string_view Reader::peek() const
{
  if ( buffer.empty() ) {
    return {};
  }
  return string_view( &buffer.front(), 1 );
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  while ( len > 0 ) {
    if ( buffer.empty() ) {
      break;
    }
    buffer.pop();
    len--;
    g_bytes_popped++;
  }
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return buffer.size();
}
