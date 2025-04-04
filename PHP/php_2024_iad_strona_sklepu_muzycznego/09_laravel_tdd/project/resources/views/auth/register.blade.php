<x-guest-layout>
    <div class="text-center mb-6">
        <h1 class="font-bold text-gray-600" style="font-size: 2rem;">{{ __('Rejestracja') }}</h1>
    </div>
    <form method="POST" action="{{ route('register') }}">
        @csrf

        <!-- Name -->
        <div>
            <x-input-label for="name" :value="__('Imię')" />
            <x-text-input id="name" class="block mt-1 w-full focus:border-gray-300 focus:ring-1" type="text" name="name" :value="old('name')" required autofocus autocomplete="name" />
            <x-input-error :messages="$errors->get('name')" class="mt-2" />
        </div>

        <!-- Email Address -->
        <div class="mt-4">
            <x-input-label for="email" :value="__('Email')" />
            <x-text-input id="email" class="block mt-1 w-full focus:border-gray-300 focus:ring-1" type="email" name="email" :value="old('email')" required autocomplete="username" />
            <x-input-error :messages="$errors->get('email')" class="mt-2" />
        </div>

        <!-- Password -->
        <div class="mt-4">
            <x-input-label for="password" :value="__('Hasło')" />

            <x-text-input id="password" class="block mt-1 w-full focus:border-gray-300 focus:ring-1"
                            type="password"
                            name="password"
                            required autocomplete="new-password" />

            <x-input-error :messages="$errors->get('password')" class="mt-2" />
        </div>

        <!-- Confirm Password -->
        <div class="mt-4">
            <x-input-label for="password_confirmation" :value="__('Powtórz hasło')" />

            <x-text-input id="password_confirmation" class="block mt-1 w-full focus:border-gray-300 focus:ring-1"
                            type="password"
                            name="password_confirmation" required autocomplete="new-password" />

            <x-input-error :messages="$errors->get('password_confirmation')" class="mt-2" />
        </div>

        <div class="flex items-center justify-center mt-4">
            <a class="underline text-sm text-gray-600 hover:text-gray-900 rounded-md focus:outline-none focus:ring-1 focus:ring-offset-2 focus:ring-gray-500" href="{{ route('login') }}">
                {{ __('Masz już konto? Zaloguj się') }}
            </a>
        </div>

        <div class="flex items-center justify-center mt-4" >
            <x-primary-button class="ms-5">
                {{ __('Zarejestruj się') }}
            </x-primary-button>
        </div>
    </form>
</x-guest-layout>
