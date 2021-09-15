// # Pattern 1. Returning Results: thread writing result to a reference
void f(const vector<double>& v, double∗ res); // take input from v; place result in *res
class F {
public:
	F(const vector<double>& vv, double∗ p) :v{vv}, res{p} { }
	void operator()(); // place result in *res
private:
	const vector<double>& v; // source of input
	double∗ res; // target for output
};

double g(const vector<double>&); // use return value
void user(vector<double>& vec1, vector<double> vec2, vector<double> vec3)
{
	double res1; double res2; double res3;
	thread t1 {f,cref(vec1),&res1}; thread t2 {F{vec2,&res2}};
	thread t3 { [&](){ res3 = g(vec3); } };

	t1.join();
	t2.join();
	t3.join();

	cout << res1 << ' ' << res2 << ' ' << res3 << '\n';
}


// # Pattern 2. Wating Events: communicating with message queue and condition_variable

class Message { // object to be communicated
	//...
};
queue<Message> mqueue; // the queue of messages
condition_variable mcond; // the variable communicating events
mutex mmutex; // for synchronizing access to mcond

void consumer() {
	while(true) {
		unique_lock lck {mmutex}; // acquire mmutex
		mcond.wait(lck,[] { return !mqueue.empty(); });
		// release lck and wait;
		// re-acquire lck upon wakeup
		// don’t wake up unless mqueue is non-empty

		auto m = mqueue.front(); // get the message
		mqueue.pop();
		lck.unlock(); // release lck
		// ... process m ...
	}
}

void producer() {
	while(true) {
		Message m;
		// ... fill the message ...
		scoped_lock lck {mmutex}; mqueue.push(m);
		mcond.notify_one();
		//notify
		// release lock (at end of scope)
	}
}

// ## Promise, Future, packaged_task, async()

void f(promise<X>& px) // a task: place the result in px
{
	// ...
	try {
		X res;
		// ... compute a value for res ...
		px.set_value(res);
	}
	catch (...) {
		// oops: couldn’t compute res
		px.set_exception(current_exception()); // pass the exception to the future’s thread
	}
}

void g(future<X>& fx)
{
	// ...
	try {
		X v = fx.get(); // if necessary, wait for the value to get computed
		// ... use v ...
	}
	catch (...) {
		// ... handle error ...
	}
}


double comp4(vector<double>& v) // spawn many tasks if v is large enough
{
	if (v.size()<10000) // is it worth using concurrency?
		return accum(v.begin(),v.end(),0.0);

	auto v0 = &v[0]; auto sz = v.size();
	auto f0 = async(accum,v0,v0+sz/4,0.0); // first quarter
	auto f1 = async(accum,v0+sz/4,v0+sz/2,0.0); // second quarter
	auto f2 = async(accum,v0+sz/2,v0+sz∗3/4,0.0); // third quarter
	auto f3 = async(accum,v0+sz∗3/4,v0+sz,0.0); // four th quar ter

	return f0.get()+f1.get()+f2.get()+f3.get(); // collect and combine the results
}
