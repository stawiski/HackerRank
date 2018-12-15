#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Message {
public:
    Message() {}
    Message(std::string text, int id):
        text_(text),
        id_(id)
        {}
    /* Message text getter. */
    const string& get_text() const {
        return this->text_;
    }
    /* Message ID getter. */
    const int get_id() const {
        return this->id_;
    }
    /* Overload "<"" for std::sort(). */
    bool operator< (const Message &msg) const {
        /* Compare Message IDs. */
        if (this->get_id() < msg.get_id()) {
            return true;
        } else {
            return false;
        }
    }
private:
    /* Message text. */
    std::string text_;
    /* Unique Message ID. */
    int id_;
};

class MessageFactory {
public:
    MessageFactory() {}
    Message create_message(const string& text) {\
        /* Return new Message with unique ID, increase unique ID. */
        return Message(text, msgId++);
    }
private:
    /* Unique Message ID counter. */
    static int msgId;
};

int MessageFactory::msgId = 0;

class Recipient {
public:
    Recipient() {}
    void receive(const Message& msg) {
        messages_.push_back(msg);
    }
    void print_messages() {
        fix_order();
        for (auto& msg : messages_) {
            cout << msg.get_text() << endl;
        }
        messages_.clear();
    }
private:
    void fix_order() {
        sort(messages_.begin(), messages_.end());
    }
    vector<Message> messages_;
};

class Network {
public:
    static void send_messages(vector<Message> messages, Recipient& recipient) {
    // simulates the unpredictable network, where sent messages might arrive in unspecified order
        random_shuffle(messages.begin(), messages.end());         
        for (auto msg : messages) {
            recipient.receive(msg);
        }
    }
};



int main() {
    MessageFactory message_factory;
    Recipient recipient;
    vector<Message> messages;
    string text;
    while (getline(cin, text)) {
        messages.push_back(message_factory.create_message(text));
    }
    Network::send_messages(messages, recipient);
    recipient.print_messages();
}
